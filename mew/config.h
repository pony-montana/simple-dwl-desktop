/* See LICENSE file for copyright and license details. */
/* Default settings; can be overriden by command line. */

static int top              = 1;                       /* -b option; if 0, appear at bottom */
static const char *fonts[]  = { "monospace:size=10" }; /* -f option overrides fonts[0] */
static const char *prompt   = NULL;                    /* -p option; prompt to the left of input field */
static uint32_t colors[][2] = {
	/*               fg         bg          */
	[SchemeNorm] = { 0xbbbbbbff, 0x222222ff },
	[SchemeSel]  = { 0xeeeeeeff, 0x005577ff },
	[SchemeOut]  = { 0x000000ff, 0x00ffffff },
};

/* -m option; if provided, use that output instead of default output */
static const char *output_name = NULL;

/* -l option; if nonzero, use vertical list with given number of lines */
static unsigned int lines      = 0;

/*
 * Characters not considered part of a word while deleting words
 * for example: " /?\"&[]"
 */
static const char worddelimiters[] = " ";
