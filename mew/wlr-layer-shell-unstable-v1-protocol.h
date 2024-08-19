/* Generated by wayland-scanner 1.22.0 */

#ifndef WLR_LAYER_SHELL_UNSTABLE_V1_CLIENT_PROTOCOL_H
#define WLR_LAYER_SHELL_UNSTABLE_V1_CLIENT_PROTOCOL_H

#include <stdint.h>
#include <stddef.h>
#include "wayland-client.h"

#ifdef  __cplusplus
extern "C" {
#endif

/**
 * @page page_wlr_layer_shell_unstable_v1 The wlr_layer_shell_unstable_v1 protocol
 * @section page_ifaces_wlr_layer_shell_unstable_v1 Interfaces
 * - @subpage page_iface_zwlr_layer_shell_v1 - create surfaces that are layers of the desktop
 * - @subpage page_iface_zwlr_layer_surface_v1 - layer metadata interface
 * @section page_copyright_wlr_layer_shell_unstable_v1 Copyright
 * <pre>
 *
 * Copyright © 2017 Drew DeVault
 *
 * Permission to use, copy, modify, distribute, and sell this
 * software and its documentation for any purpose is hereby granted
 * without fee, provided that the above copyright notice appear in
 * all copies and that both that copyright notice and this permission
 * notice appear in supporting documentation, and that the name of
 * the copyright holders not be used in advertising or publicity
 * pertaining to distribution of the software without specific,
 * written prior permission.  The copyright holders make no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied
 * warranty.
 *
 * THE COPYRIGHT HOLDERS DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS, IN NO EVENT SHALL THE COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN
 * AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
 * ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF
 * THIS SOFTWARE.
 * </pre>
 */
struct wl_output;
struct wl_surface;
struct xdg_popup;
struct zwlr_layer_shell_v1;
struct zwlr_layer_surface_v1;

#ifndef ZWLR_LAYER_SHELL_V1_INTERFACE
#define ZWLR_LAYER_SHELL_V1_INTERFACE
/**
 * @page page_iface_zwlr_layer_shell_v1 zwlr_layer_shell_v1
 * @section page_iface_zwlr_layer_shell_v1_desc Description
 *
 * Clients can use this interface to assign the surface_layer role to
 * wl_surfaces. Such surfaces are assigned to a "layer" of the output and
 * rendered with a defined z-depth respective to each other. They may also be
 * anchored to the edges and corners of a screen and specify input handling
 * semantics. This interface should be suitable for the implementation of
 * many desktop shell components, and a broad number of other applications
 * that interact with the desktop.
 * @section page_iface_zwlr_layer_shell_v1_api API
 * See @ref iface_zwlr_layer_shell_v1.
 */
/**
 * @defgroup iface_zwlr_layer_shell_v1 The zwlr_layer_shell_v1 interface
 *
 * Clients can use this interface to assign the surface_layer role to
 * wl_surfaces. Such surfaces are assigned to a "layer" of the output and
 * rendered with a defined z-depth respective to each other. They may also be
 * anchored to the edges and corners of a screen and specify input handling
 * semantics. This interface should be suitable for the implementation of
 * many desktop shell components, and a broad number of other applications
 * that interact with the desktop.
 */
extern const struct wl_interface zwlr_layer_shell_v1_interface;
#endif
#ifndef ZWLR_LAYER_SURFACE_V1_INTERFACE
#define ZWLR_LAYER_SURFACE_V1_INTERFACE
/**
 * @page page_iface_zwlr_layer_surface_v1 zwlr_layer_surface_v1
 * @section page_iface_zwlr_layer_surface_v1_desc Description
 *
 * An interface that may be implemented by a wl_surface, for surfaces that
 * are designed to be rendered as a layer of a stacked desktop-like
 * environment.
 *
 * Layer surface state (size, anchor, exclusive zone, margin, interactivity)
 * is double-buffered, and will be applied at the time wl_surface.commit of
 * the corresponding wl_surface is called.
 * @section page_iface_zwlr_layer_surface_v1_api API
 * See @ref iface_zwlr_layer_surface_v1.
 */
/**
 * @defgroup iface_zwlr_layer_surface_v1 The zwlr_layer_surface_v1 interface
 *
 * An interface that may be implemented by a wl_surface, for surfaces that
 * are designed to be rendered as a layer of a stacked desktop-like
 * environment.
 *
 * Layer surface state (size, anchor, exclusive zone, margin, interactivity)
 * is double-buffered, and will be applied at the time wl_surface.commit of
 * the corresponding wl_surface is called.
 */
extern const struct wl_interface zwlr_layer_surface_v1_interface;
#endif

#ifndef ZWLR_LAYER_SHELL_V1_ERROR_ENUM
#define ZWLR_LAYER_SHELL_V1_ERROR_ENUM
enum zwlr_layer_shell_v1_error {
	/**
	 * wl_surface has another role
	 */
	ZWLR_LAYER_SHELL_V1_ERROR_ROLE = 0,
	/**
	 * layer value is invalid
	 */
	ZWLR_LAYER_SHELL_V1_ERROR_INVALID_LAYER = 1,
	/**
	 * wl_surface has a buffer attached or committed
	 */
	ZWLR_LAYER_SHELL_V1_ERROR_ALREADY_CONSTRUCTED = 2,
};
#endif /* ZWLR_LAYER_SHELL_V1_ERROR_ENUM */

#ifndef ZWLR_LAYER_SHELL_V1_LAYER_ENUM
#define ZWLR_LAYER_SHELL_V1_LAYER_ENUM
/**
 * @ingroup iface_zwlr_layer_shell_v1
 * available layers for surfaces
 *
 * These values indicate which layers a surface can be rendered in. They
 * are ordered by z depth, bottom-most first. Traditional shell surfaces
 * will typically be rendered between the bottom and top layers.
 * Fullscreen shell surfaces are typically rendered at the top layer.
 * Multiple surfaces can share a single layer, and ordering within a
 * single layer is undefined.
 */
enum zwlr_layer_shell_v1_layer {
	ZWLR_LAYER_SHELL_V1_LAYER_BACKGROUND = 0,
	ZWLR_LAYER_SHELL_V1_LAYER_BOTTOM = 1,
	ZWLR_LAYER_SHELL_V1_LAYER_TOP = 2,
	ZWLR_LAYER_SHELL_V1_LAYER_OVERLAY = 3,
};
#endif /* ZWLR_LAYER_SHELL_V1_LAYER_ENUM */

#define ZWLR_LAYER_SHELL_V1_GET_LAYER_SURFACE 0


/**
 * @ingroup iface_zwlr_layer_shell_v1
 */
#define ZWLR_LAYER_SHELL_V1_GET_LAYER_SURFACE_SINCE_VERSION 1

/** @ingroup iface_zwlr_layer_shell_v1 */
static inline void
zwlr_layer_shell_v1_set_user_data(struct zwlr_layer_shell_v1 *zwlr_layer_shell_v1, void *user_data)
{
	wl_proxy_set_user_data((struct wl_proxy *) zwlr_layer_shell_v1, user_data);
}

/** @ingroup iface_zwlr_layer_shell_v1 */
static inline void *
zwlr_layer_shell_v1_get_user_data(struct zwlr_layer_shell_v1 *zwlr_layer_shell_v1)
{
	return wl_proxy_get_user_data((struct wl_proxy *) zwlr_layer_shell_v1);
}

static inline uint32_t
zwlr_layer_shell_v1_get_version(struct zwlr_layer_shell_v1 *zwlr_layer_shell_v1)
{
	return wl_proxy_get_version((struct wl_proxy *) zwlr_layer_shell_v1);
}

/** @ingroup iface_zwlr_layer_shell_v1 */
static inline void
zwlr_layer_shell_v1_destroy(struct zwlr_layer_shell_v1 *zwlr_layer_shell_v1)
{
	wl_proxy_destroy((struct wl_proxy *) zwlr_layer_shell_v1);
}

/**
 * @ingroup iface_zwlr_layer_shell_v1
 *
 * Create a layer surface for an existing surface. This assigns the role of
 * layer_surface, or raises a protocol error if another role is already
 * assigned.
 *
 * Creating a layer surface from a wl_surface which has a buffer attached
 * or committed is a client error, and any attempts by a client to attach
 * or manipulate a buffer prior to the first layer_surface.configure call
 * must also be treated as errors.
 *
 * You may pass NULL for output to allow the compositor to decide which
 * output to use. Generally this will be the one that the user most
 * recently interacted with.
 *
 * Clients can specify a namespace that defines the purpose of the layer
 * surface.
 */
static inline struct zwlr_layer_surface_v1 *
zwlr_layer_shell_v1_get_layer_surface(struct zwlr_layer_shell_v1 *zwlr_layer_shell_v1, struct wl_surface *surface, struct wl_output *output, uint32_t layer, const char *namespace)
{
	struct wl_proxy *id;

	id = wl_proxy_marshal_flags((struct wl_proxy *) zwlr_layer_shell_v1,
			 ZWLR_LAYER_SHELL_V1_GET_LAYER_SURFACE, &zwlr_layer_surface_v1_interface, wl_proxy_get_version((struct wl_proxy *) zwlr_layer_shell_v1), 0, NULL, surface, output, layer, namespace);

	return (struct zwlr_layer_surface_v1 *) id;
}

#ifndef ZWLR_LAYER_SURFACE_V1_ERROR_ENUM
#define ZWLR_LAYER_SURFACE_V1_ERROR_ENUM
enum zwlr_layer_surface_v1_error {
	/**
	 * provided surface state is invalid
	 */
	ZWLR_LAYER_SURFACE_V1_ERROR_INVALID_SURFACE_STATE = 0,
	/**
	 * size is invalid
	 */
	ZWLR_LAYER_SURFACE_V1_ERROR_INVALID_SIZE = 1,
	/**
	 * anchor bitfield is invalid
	 */
	ZWLR_LAYER_SURFACE_V1_ERROR_INVALID_ANCHOR = 2,
};
#endif /* ZWLR_LAYER_SURFACE_V1_ERROR_ENUM */

#ifndef ZWLR_LAYER_SURFACE_V1_ANCHOR_ENUM
#define ZWLR_LAYER_SURFACE_V1_ANCHOR_ENUM
enum zwlr_layer_surface_v1_anchor {
	/**
	 * the top edge of the anchor rectangle
	 */
	ZWLR_LAYER_SURFACE_V1_ANCHOR_TOP = 1,
	/**
	 * the bottom edge of the anchor rectangle
	 */
	ZWLR_LAYER_SURFACE_V1_ANCHOR_BOTTOM = 2,
	/**
	 * the left edge of the anchor rectangle
	 */
	ZWLR_LAYER_SURFACE_V1_ANCHOR_LEFT = 4,
	/**
	 * the right edge of the anchor rectangle
	 */
	ZWLR_LAYER_SURFACE_V1_ANCHOR_RIGHT = 8,
};
#endif /* ZWLR_LAYER_SURFACE_V1_ANCHOR_ENUM */

/**
 * @ingroup iface_zwlr_layer_surface_v1
 * @struct zwlr_layer_surface_v1_listener
 */
struct zwlr_layer_surface_v1_listener {
	/**
	 * suggest a surface change
	 *
	 * The configure event asks the client to resize its surface.
	 *
	 * Clients should arrange their surface for the new states, and
	 * then send an ack_configure request with the serial sent in this
	 * configure event at some point before committing the new surface.
	 *
	 * The client is free to dismiss all but the last configure event
	 * it received.
	 *
	 * The width and height arguments specify the size of the window in
	 * surface-local coordinates.
	 *
	 * The size is a hint, in the sense that the client is free to
	 * ignore it if it doesn't resize, pick a smaller size (to satisfy
	 * aspect ratio or resize in steps of NxM pixels). If the client
	 * picks a smaller size and is anchored to two opposite anchors
	 * (e.g. 'top' and 'bottom'), the surface will be centered on this
	 * axis.
	 *
	 * If the width or height arguments are zero, it means the client
	 * should decide its own window dimension.
	 */
	void (*configure)(void *data,
			  struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1,
			  uint32_t serial,
			  uint32_t width,
			  uint32_t height);
	/**
	 * surface should be closed
	 *
	 * The closed event is sent by the compositor when the surface
	 * will no longer be shown. The output may have been destroyed or
	 * the user may have asked for it to be removed. Further changes to
	 * the surface will be ignored. The client should destroy the
	 * resource after receiving this event, and create a new surface if
	 * they so choose.
	 */
	void (*closed)(void *data,
		       struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1);
};

/**
 * @ingroup iface_zwlr_layer_surface_v1
 */
static inline int
zwlr_layer_surface_v1_add_listener(struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1,
				   const struct zwlr_layer_surface_v1_listener *listener, void *data)
{
	return wl_proxy_add_listener((struct wl_proxy *) zwlr_layer_surface_v1,
				     (void (**)(void)) listener, data);
}

#define ZWLR_LAYER_SURFACE_V1_SET_SIZE 0
#define ZWLR_LAYER_SURFACE_V1_SET_ANCHOR 1
#define ZWLR_LAYER_SURFACE_V1_SET_EXCLUSIVE_ZONE 2
#define ZWLR_LAYER_SURFACE_V1_SET_MARGIN 3
#define ZWLR_LAYER_SURFACE_V1_SET_KEYBOARD_INTERACTIVITY 4
#define ZWLR_LAYER_SURFACE_V1_GET_POPUP 5
#define ZWLR_LAYER_SURFACE_V1_ACK_CONFIGURE 6
#define ZWLR_LAYER_SURFACE_V1_DESTROY 7

/**
 * @ingroup iface_zwlr_layer_surface_v1
 */
#define ZWLR_LAYER_SURFACE_V1_CONFIGURE_SINCE_VERSION 1
/**
 * @ingroup iface_zwlr_layer_surface_v1
 */
#define ZWLR_LAYER_SURFACE_V1_CLOSED_SINCE_VERSION 1

/**
 * @ingroup iface_zwlr_layer_surface_v1
 */
#define ZWLR_LAYER_SURFACE_V1_SET_SIZE_SINCE_VERSION 1
/**
 * @ingroup iface_zwlr_layer_surface_v1
 */
#define ZWLR_LAYER_SURFACE_V1_SET_ANCHOR_SINCE_VERSION 1
/**
 * @ingroup iface_zwlr_layer_surface_v1
 */
#define ZWLR_LAYER_SURFACE_V1_SET_EXCLUSIVE_ZONE_SINCE_VERSION 1
/**
 * @ingroup iface_zwlr_layer_surface_v1
 */
#define ZWLR_LAYER_SURFACE_V1_SET_MARGIN_SINCE_VERSION 1
/**
 * @ingroup iface_zwlr_layer_surface_v1
 */
#define ZWLR_LAYER_SURFACE_V1_SET_KEYBOARD_INTERACTIVITY_SINCE_VERSION 1
/**
 * @ingroup iface_zwlr_layer_surface_v1
 */
#define ZWLR_LAYER_SURFACE_V1_GET_POPUP_SINCE_VERSION 1
/**
 * @ingroup iface_zwlr_layer_surface_v1
 */
#define ZWLR_LAYER_SURFACE_V1_ACK_CONFIGURE_SINCE_VERSION 1
/**
 * @ingroup iface_zwlr_layer_surface_v1
 */
#define ZWLR_LAYER_SURFACE_V1_DESTROY_SINCE_VERSION 1

/** @ingroup iface_zwlr_layer_surface_v1 */
static inline void
zwlr_layer_surface_v1_set_user_data(struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1, void *user_data)
{
	wl_proxy_set_user_data((struct wl_proxy *) zwlr_layer_surface_v1, user_data);
}

/** @ingroup iface_zwlr_layer_surface_v1 */
static inline void *
zwlr_layer_surface_v1_get_user_data(struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1)
{
	return wl_proxy_get_user_data((struct wl_proxy *) zwlr_layer_surface_v1);
}

static inline uint32_t
zwlr_layer_surface_v1_get_version(struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1)
{
	return wl_proxy_get_version((struct wl_proxy *) zwlr_layer_surface_v1);
}

/**
 * @ingroup iface_zwlr_layer_surface_v1
 *
 * Sets the size of the surface in surface-local coordinates. The
 * compositor will display the surface centered with respect to its
 * anchors.
 *
 * If you pass 0 for either value, the compositor will assign it and
 * inform you of the assignment in the configure event. You must set your
 * anchor to opposite edges in the dimensions you omit; not doing so is a
 * protocol error. Both values are 0 by default.
 *
 * Size is double-buffered, see wl_surface.commit.
 */
static inline void
zwlr_layer_surface_v1_set_size(struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1, uint32_t width, uint32_t height)
{
	wl_proxy_marshal_flags((struct wl_proxy *) zwlr_layer_surface_v1,
			 ZWLR_LAYER_SURFACE_V1_SET_SIZE, NULL, wl_proxy_get_version((struct wl_proxy *) zwlr_layer_surface_v1), 0, width, height);
}

/**
 * @ingroup iface_zwlr_layer_surface_v1
 *
 * Requests that the compositor anchor the surface to the specified edges
 * and corners. If two orthoginal edges are specified (e.g. 'top' and
 * 'left'), then the anchor point will be the intersection of the edges
 * (e.g. the top left corner of the output); otherwise the anchor point
 * will be centered on that edge, or in the center if none is specified.
 *
 * Anchor is double-buffered, see wl_surface.commit.
 */
static inline void
zwlr_layer_surface_v1_set_anchor(struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1, uint32_t anchor)
{
	wl_proxy_marshal_flags((struct wl_proxy *) zwlr_layer_surface_v1,
			 ZWLR_LAYER_SURFACE_V1_SET_ANCHOR, NULL, wl_proxy_get_version((struct wl_proxy *) zwlr_layer_surface_v1), 0, anchor);
}

/**
 * @ingroup iface_zwlr_layer_surface_v1
 *
 * Requests that the compositor avoids occluding an area of the surface
 * with other surfaces. The compositor's use of this information is
 * implementation-dependent - do not assume that this region will not
 * actually be occluded.
 *
 * A positive value is only meaningful if the surface is anchored to an
 * edge, rather than a corner. The zone is the number of surface-local
 * coordinates from the edge that are considered exclusive.
 *
 * Surfaces that do not wish to have an exclusive zone may instead specify
 * how they should interact with surfaces that do. If set to zero, the
 * surface indicates that it would like to be moved to avoid occluding
 * surfaces with a positive excluzive zone. If set to -1, the surface
 * indicates that it would not like to be moved to accommodate for other
 * surfaces, and the compositor should extend it all the way to the edges
 * it is anchored to.
 *
 * For example, a panel might set its exclusive zone to 10, so that
 * maximized shell surfaces are not shown on top of it. A notification
 * might set its exclusive zone to 0, so that it is moved to avoid
 * occluding the panel, but shell surfaces are shown underneath it. A
 * wallpaper or lock screen might set their exclusive zone to -1, so that
 * they stretch below or over the panel.
 *
 * The default value is 0.
 *
 * Exclusive zone is double-buffered, see wl_surface.commit.
 */
static inline void
zwlr_layer_surface_v1_set_exclusive_zone(struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1, int32_t zone)
{
	wl_proxy_marshal_flags((struct wl_proxy *) zwlr_layer_surface_v1,
			 ZWLR_LAYER_SURFACE_V1_SET_EXCLUSIVE_ZONE, NULL, wl_proxy_get_version((struct wl_proxy *) zwlr_layer_surface_v1), 0, zone);
}

/**
 * @ingroup iface_zwlr_layer_surface_v1
 *
 * Requests that the surface be placed some distance away from the anchor
 * point on the output, in surface-local coordinates. Setting this value
 * for edges you are not anchored to has no effect.
 *
 * The exclusive zone includes the margin.
 *
 * Margin is double-buffered, see wl_surface.commit.
 */
static inline void
zwlr_layer_surface_v1_set_margin(struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1, int32_t top, int32_t right, int32_t bottom, int32_t left)
{
	wl_proxy_marshal_flags((struct wl_proxy *) zwlr_layer_surface_v1,
			 ZWLR_LAYER_SURFACE_V1_SET_MARGIN, NULL, wl_proxy_get_version((struct wl_proxy *) zwlr_layer_surface_v1), 0, top, right, bottom, left);
}

/**
 * @ingroup iface_zwlr_layer_surface_v1
 *
 * Set to 1 to request that the seat send keyboard events to this layer
 * surface. For layers below the shell surface layer, the seat will use
 * normal focus semantics. For layers above the shell surface layers, the
 * seat will always give exclusive keyboard focus to the top-most layer
 * which has keyboard interactivity set to true.
 *
 * Layer surfaces receive pointer, touch, and tablet events normally. If
 * you do not want to receive them, set the input region on your surface
 * to an empty region.
 *
 * Events is double-buffered, see wl_surface.commit.
 */
static inline void
zwlr_layer_surface_v1_set_keyboard_interactivity(struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1, uint32_t keyboard_interactivity)
{
	wl_proxy_marshal_flags((struct wl_proxy *) zwlr_layer_surface_v1,
			 ZWLR_LAYER_SURFACE_V1_SET_KEYBOARD_INTERACTIVITY, NULL, wl_proxy_get_version((struct wl_proxy *) zwlr_layer_surface_v1), 0, keyboard_interactivity);
}

/**
 * @ingroup iface_zwlr_layer_surface_v1
 *
 * This assigns an xdg_popup's parent to this layer_surface.  This popup
 * should have been created via xdg_surface::get_popup with the parent set
 * to NULL, and this request must be invoked before committing the popup's
 * initial state.
 *
 * See the documentation of xdg_popup for more details about what an
 * xdg_popup is and how it is used.
 */
static inline void
zwlr_layer_surface_v1_get_popup(struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1, struct xdg_popup *popup)
{
	wl_proxy_marshal_flags((struct wl_proxy *) zwlr_layer_surface_v1,
			 ZWLR_LAYER_SURFACE_V1_GET_POPUP, NULL, wl_proxy_get_version((struct wl_proxy *) zwlr_layer_surface_v1), 0, popup);
}

/**
 * @ingroup iface_zwlr_layer_surface_v1
 *
 * When a configure event is received, if a client commits the
 * surface in response to the configure event, then the client
 * must make an ack_configure request sometime before the commit
 * request, passing along the serial of the configure event.
 *
 * If the client receives multiple configure events before it
 * can respond to one, it only has to ack the last configure event.
 *
 * A client is not required to commit immediately after sending
 * an ack_configure request - it may even ack_configure several times
 * before its next surface commit.
 *
 * A client may send multiple ack_configure requests before committing, but
 * only the last request sent before a commit indicates which configure
 * event the client really is responding to.
 */
static inline void
zwlr_layer_surface_v1_ack_configure(struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1, uint32_t serial)
{
	wl_proxy_marshal_flags((struct wl_proxy *) zwlr_layer_surface_v1,
			 ZWLR_LAYER_SURFACE_V1_ACK_CONFIGURE, NULL, wl_proxy_get_version((struct wl_proxy *) zwlr_layer_surface_v1), 0, serial);
}

/**
 * @ingroup iface_zwlr_layer_surface_v1
 *
 * This request destroys the layer surface.
 */
static inline void
zwlr_layer_surface_v1_destroy(struct zwlr_layer_surface_v1 *zwlr_layer_surface_v1)
{
	wl_proxy_marshal_flags((struct wl_proxy *) zwlr_layer_surface_v1,
			 ZWLR_LAYER_SURFACE_V1_DESTROY, NULL, wl_proxy_get_version((struct wl_proxy *) zwlr_layer_surface_v1), WL_MARSHAL_FLAG_DESTROY);
}

#ifdef  __cplusplus
}
#endif

#endif
