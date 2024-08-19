#define _DEFAULT_SOURCE
#include <err.h>
#include <errno.h>
#include <getopt.h>
#include <limits.h>
#include <pwd.h>
#include <shadow.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <wayland-client.h>
#include <xkbcommon/xkbcommon.h>

#include "ext-session-lock-v1-protocol.h"
#include "single-pixel-buffer-v1-protocol.h"
#include "viewporter-protocol.h"

typedef struct {
	unsigned int r, g, b;
} Clr;

typedef struct {
	struct wl_keyboard *keyboard;
	struct xkb_keymap *keymap;
	struct xkb_state *state;
} Keyboard;

typedef struct {
	struct wl_seat *seat;
	Keyboard *kb;
	struct wl_list link;
} Seat;

static struct {
	char input[256];
	int len;
} pw;

typedef struct {
	uint32_t wl_name;
	struct wl_output *wl_output;
	struct wl_surface *surface;
	struct ext_session_lock_surface_v1 *lock_surface;
	struct wp_viewport *viewport;

	const char *name;
	int32_t width, height;

	struct wl_list link;
} Output;



static struct wl_display *display;
static struct wl_registry *registry;
static struct wl_compositor *compositor;
static struct wp_viewporter *viewporter;
static struct ext_session_lock_v1 *lock;
static struct ext_session_lock_manager_v1 *lock_manager;
static struct wp_single_pixel_buffer_manager_v1 *buf_manager;
static struct xkb_context *xkb_ctx;

static struct wl_list outputs;
static struct wl_list seats;

static char *hash;
static bool locked, running;

enum input_state { INIT, FAILED, INPUT, INPUT_ALT } input_state = INIT;

static Clr colorname[4] = {
	[INIT]      = { 0x00000000, 0x00000000, 0x00000000 }, /* after initialization */
	[INPUT]     = { 0x00000000, 0x55555555, 0x77777777 }, /* during input */
	[INPUT_ALT] = { 0x00000000, 0x50505050, 0x70707070 }, /* during input, second color */
	[FAILED]    = { 0xcccccccc, 0x33333333, 0x33333333 }, /* wrong password */
};

static void
noop()
{
	// :3c
}

static Clr
parse_clr(const char *color)
{
	int len;
	unsigned int res;

	len = strlen(color);
	if (len != 6)
		errx(EXIT_FAILURE, "invalid color given: %s", color);

	res = strtoul(color, NULL, 16);

	return (Clr){
		((res >> 16) & 0xff) * (0xffffffff / 0xff),
		((res >> 8) & 0xff) * (0xffffffff / 0xff),
		((res >> 0) & 0xff) * (0xffffffff / 0xff),
	};
}

static void
output_frame(Output *output)
{
	Clr c = colorname[input_state];
	struct wl_buffer *buffer;
	struct wl_region *opaque = wl_compositor_create_region(compositor);

	/* alpha has no effect on this surface */
	buffer = wp_single_pixel_buffer_manager_v1_create_u32_rgba_buffer(
		buf_manager, c.r, c.g, c.b, 0xffffffff);

	wl_surface_attach(output->surface, buffer, 0, 0);
	wl_surface_damage_buffer(output->surface, 0, 0, INT32_MAX, INT32_MAX);
	wl_region_add(opaque, 0, 0, INT32_MAX, INT32_MAX);
	wl_surface_set_opaque_region(output->surface, opaque);
	wl_region_destroy(opaque);
	wp_viewport_set_destination(output->viewport, output->width, output->height);
	wl_surface_commit(output->surface);

	wl_buffer_destroy(buffer);
}

static void
outputs_frame(void)
{
	Output *output;

	wl_list_for_each(output, &outputs, link)
		output_frame(output);
}

static void
lock_surface_configure(void *data,
		struct ext_session_lock_surface_v1 *lock_surface,
		uint32_t serial, uint32_t width, uint32_t height)
{
	Output *output = data;
	output->width = width;
	output->height = height;

	ext_session_lock_surface_v1_ack_configure(lock_surface, serial);
	output_frame(output);
}

static const struct ext_session_lock_surface_v1_listener lock_surface_listener = {
	.configure = lock_surface_configure,
};

static void
output_create_surface(Output *output)
{
	output->surface = wl_compositor_create_surface(compositor);
	output->lock_surface = ext_session_lock_v1_get_lock_surface(
		lock, output->surface, output->wl_output);
	output->viewport = wp_viewporter_get_viewport(viewporter, output->surface);

	ext_session_lock_surface_v1_add_listener(output->lock_surface, &lock_surface_listener, output);
}

static void
output_destroy(Output *output)
{
	wl_list_remove(&output->link);
	wp_viewport_destroy(output->viewport);
	ext_session_lock_surface_v1_destroy(output->lock_surface);
	wl_surface_destroy(output->surface);
	wl_output_destroy(output->wl_output);
	free(output);
}

static void
outputs_destroy(void)
{
	Output *output, *tmp;

	wl_list_for_each_safe(output, tmp, &outputs, link)
		output_destroy(output);
}

static void
keyboard_keypress(enum wl_keyboard_key_state key_state,
		xkb_keysym_t sym)
{
	int n;
	char buf[8], *inputhash;

	if (key_state != WL_KEYBOARD_KEY_STATE_PRESSED)
		return;

	switch (sym) {
	case XKB_KEY_KP_Enter:
	case XKB_KEY_Return:
		pw.input[pw.len] = '\0';
		errno = 0;
		if (!(inputhash = crypt(pw.input, hash)))
			warn("crypt:");
		else
			running = !!strcmp(inputhash, hash);
		if (running)
			input_state = FAILED;
		explicit_bzero(&pw.input, sizeof(pw.input));
		pw.len = 0;
		break;
	case XKB_KEY_BackSpace:
		if (pw.len)
			pw.input[--pw.len] = '\0';
		break;
	case XKB_KEY_Escape:
		explicit_bzero(&pw.input, sizeof(pw.input));
		pw.len = 0;
		break;
	default:
		if (!xkb_keysym_to_utf8(sym, buf, 8))
			break;
		n = strnlen(buf, 8);
		if (pw.len + n < 256) {
			memcpy(pw.input + pw.len, buf, n);
			pw.len += n;
		}
		break;
	}

	input_state = pw.len ? pw.len % 2 ? INPUT : INPUT_ALT :
	              input_state == FAILED ? FAILED : INIT;

	outputs_frame();
}

static void
keyboard_handle_keymap(void *data, struct wl_keyboard *wl_keyboard,
		uint32_t format, int32_t fd, uint32_t size)
{
	Seat *seat = data;
	char *map_shm;

	if (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1)
		errx(EXIT_FAILURE, "unknown keymap %d", format);

	xkb_keymap_unref(seat->kb->keymap);
	xkb_state_unref(seat->kb->state);

	map_shm = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
	if (map_shm == MAP_FAILED)
		errx(EXIT_FAILURE, "mmap keymap shm failed");

	seat->kb->keymap = xkb_keymap_new_from_buffer(xkb_ctx,
		map_shm, size, XKB_KEYMAP_FORMAT_TEXT_V1, XKB_KEYMAP_COMPILE_NO_FLAGS);
	munmap(map_shm, size);
	close(fd);

	seat->kb->state = xkb_state_new(seat->kb->keymap);
}

static void
keyboard_handle_key(void *data, struct wl_keyboard *wl_keyboard,
		uint32_t serial, uint32_t time, uint32_t key, uint32_t key_state)
{
	Seat *seat = data;

	keyboard_keypress((enum wl_keyboard_key_state)key_state,
		xkb_state_key_get_one_sym(seat->kb->state, key + 8));
}

static void
keyboard_handle_modifiers(void *data, struct wl_keyboard *wl_keyboard,
		uint32_t serial, uint32_t mods_depressed,
		uint32_t mods_latched, uint32_t mods_locked, uint32_t group)
{
	Seat *seat = data;

	xkb_state_update_mask(seat->kb->state, mods_depressed, mods_latched,
			mods_locked, 0, 0, group);
}

static const struct wl_keyboard_listener keyboard_listener = {
	.keymap = keyboard_handle_keymap,
	.enter = noop,
	.leave = noop,
	.key = keyboard_handle_key,
	.modifiers = keyboard_handle_modifiers,
	.repeat_info = noop,
};

static void
seat_capabilities(void *data, struct wl_seat *wl_seat,
		enum wl_seat_capability caps)
{
	Seat *seat = data;

	if (!(caps & WL_SEAT_CAPABILITY_KEYBOARD))
		return;

	seat->kb = calloc(1, sizeof(Keyboard));
	seat->kb->keyboard = wl_seat_get_keyboard(seat->seat);

	wl_keyboard_add_listener(seat->kb->keyboard, &keyboard_listener, seat);
}

static void
seat_destroy(Seat *seat)
{
	wl_keyboard_destroy(seat->kb->keyboard);
	xkb_keymap_unref(seat->kb->keymap);
	xkb_state_unref(seat->kb->state);
	free(seat->kb);
	wl_seat_destroy(seat->seat);
	free(seat);
}

static void
seats_destroy(void)
{
	Seat *seat, *tmp;

	wl_list_for_each_safe(seat, tmp, &seats, link)
		seat_destroy(seat);
}

static const struct wl_seat_listener seat_listener = {
	.capabilities = seat_capabilities,
	.name = noop,
};

static void
registry_global(void *data, struct wl_registry *registry,
		uint32_t name, const char *interface, uint32_t version)
{
	if (!strcmp(interface, wl_compositor_interface.name))
		compositor = wl_registry_bind(registry, name, &wl_compositor_interface, 4);
	else if (!strcmp(interface, wp_single_pixel_buffer_manager_v1_interface.name))
		buf_manager = wl_registry_bind(
			registry, name, &wp_single_pixel_buffer_manager_v1_interface, 1);
	else if (!strcmp(interface, wp_viewporter_interface.name))
		viewporter = wl_registry_bind(registry, name, &wp_viewporter_interface, 1);
	else if (!strcmp(interface, ext_session_lock_manager_v1_interface.name))
		lock_manager = wl_registry_bind(
			registry, name, &ext_session_lock_manager_v1_interface, 1);
	else if (!strcmp(interface, wl_seat_interface.name)) {
		Seat *seat = calloc(1, sizeof(Seat));
		seat->seat = wl_registry_bind(registry, name, &wl_seat_interface, 4);
		wl_seat_add_listener(seat->seat, &seat_listener, seat);
		wl_list_insert(&seats, &seat->link);
	} else if (!strcmp(interface, wl_output_interface.name)) {
		Output *output = calloc(1, sizeof(Output));
		output->wl_output = wl_registry_bind(registry, name, &wl_output_interface, 4);
		output->wl_name = name;
		wl_list_insert(&outputs, &output->link);
		if (running)
			output_create_surface (output);
	}
}

static void
registry_global_remove(void *data,
		struct wl_registry *registry, uint32_t name)
{
	Output *output, *tmp;

	wl_list_for_each_safe(output, tmp, &outputs, link) {
		if (output->wl_name == name) {
			output_destroy(output);
			break;
		}
	}
}

static const struct wl_registry_listener registry_listener = {
	.global = registry_global,
	.global_remove = registry_global_remove,
};

static void
lock_locked(void *data, struct ext_session_lock_v1 *lock)
{
	locked = true;
}

static void
lock_finished(void *data, struct ext_session_lock_v1 *lock)
{
	if (!locked)
		errx(EXIT_FAILURE, "another lockscreen is already running");
	warnx("compositor requested unlock");
}

static const struct ext_session_lock_v1_listener lock_listener = {
	.locked = lock_locked,
	.finished = lock_finished,
};

static void
drop(void)
{
	struct spwd *sp;
	struct passwd *p;

	if (!(p = getpwuid(getuid())))
		err(EXIT_FAILURE, NULL);
	hash = p->pw_passwd;
	if (!strcmp(hash, "x")) {
		if (!(sp = getspnam(p->pw_name)))
			errx(EXIT_FAILURE, "getspnam failed, ensure suid & sgid lock");
		hash = sp->sp_pwdp;
	}

	if (!crypt("", hash))
		err(EXIT_FAILURE, NULL);

	if (setgid(getgid()) != 0)
		err(EXIT_FAILURE, NULL);
	if (setuid(getuid()) != 0)
		err(EXIT_FAILURE, NULL);
	if (setuid(0) > 0 || setgid(0) > 0)
		errx(EXIT_FAILURE, "should not able to restore root");
}

static void
setup(void)
{
	Output *output;

	wl_list_init(&seats);
	wl_list_init(&outputs);

	if (!(display = wl_display_connect(NULL)))
		errx(EXIT_FAILURE, "wayland display connect failed");

	if (!(xkb_ctx = xkb_context_new(XKB_CONTEXT_NO_FLAGS)))
		errx(EXIT_FAILURE, "xkb_context_new failed");

	registry = wl_display_get_registry(display);
	wl_registry_add_listener(registry, &registry_listener, NULL);
	wl_display_roundtrip(display);

	if (!compositor || !lock_manager)
		errx(EXIT_FAILURE, "unsupported compositor");

	lock = ext_session_lock_manager_v1_lock(lock_manager);
	ext_session_lock_v1_add_listener(lock, &lock_listener, NULL);
	wl_display_roundtrip(display);

	wl_list_for_each(output, &outputs, link)
		output_create_surface(output);
}

static void
cleanup(void)
{
	ext_session_lock_v1_unlock_and_destroy(lock);
	wl_display_roundtrip(display);

	outputs_destroy();
	ext_session_lock_manager_v1_destroy(lock_manager);
	wp_single_pixel_buffer_manager_v1_destroy(buf_manager);
	wp_viewporter_destroy(viewporter);
	seats_destroy();
	xkb_context_unref(xkb_ctx);
	wl_compositor_destroy(compositor);
	wl_registry_destroy(registry);
	wl_display_disconnect(display);
}

int
main(int argc, char *argv[])
{
	int opt;

	while ((opt = getopt(argc, argv, "a:c:f:i:vh")) != -1) {
		switch (opt) {
		case 'a':
		case 'c':
		case 'f':
		case 'i':
			colorname[opt == 'f' ? FAILED : opt == 'i' ? INPUT :
			          opt == 'a' ? INPUT_ALT : INIT] = parse_clr(optarg);
			break;
		case 'v':
			puts("wlock " VERSION);
			return EXIT_SUCCESS;
		case 'h':
		default:
			fprintf(stderr, "usage: wlock [-hv] [-a input_alt_color] [-i input_color]\n"
			                "             [-c init_color] [-f fail_color]\n");
			return opt == 'h' ? EXIT_SUCCESS : EXIT_FAILURE;
		}
	}

	drop();
	setup();

	running = true;
	while (running && wl_display_dispatch(display) > 0)
		;

	cleanup();

	return EXIT_SUCCESS;
}
