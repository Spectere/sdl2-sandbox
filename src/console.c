/* console.c - VGA console emulation. */

#include <stdlib.h>

#include "console.h"
#include "font-cp437.h"
#include "log.h"
#include "palette-cga.h"
#include "video.h"

#define CHAR_PIXEL(console_x, console_y, char_x, char_y) \
	((console_y * console_width * font_width * font_height) + (char_y * console_width * font_width) + (console_x * font_width + char_x))
#define PAL_ARGB(color) \
	(0xFF000000 | (color->r << 16) | (color->g << 8) | color->b)

typedef struct {
	Uint8 r;
	Uint8 g;
	Uint8 b;
} palette_color_t;

console_char_t *console;

int console_width;
int console_height;
static short console_scale;
static SDL_bool console_double_width;
static SDL_bool console_blink;
static short console_blink_rate;
static short console_blink_state = SDL_FALSE;
static short console_blink_timer = 0;

const Uint8 font_width = 8;
static Uint8 font_height;

static Uint8 *charset = NULL;
static palette_color_t palette[16];

void console_close() {
	if(charset != NULL)
		free(charset);
}

void console_load_charset_cp437() {
	font_height = FONT_CP437_HEIGHT;

	if(charset != NULL)
		free(charset);

	charset = malloc(FONT_CP437_SIZE * sizeof(Uint8));
	memcpy(charset, FONT_CP437, FONT_CP437_SIZE);

	lprint(INFO, "%ix%i font loaded (cp437).", font_width, font_height);
}

void console_load_palette_cga() {
	int i;

	/* Load the palette. */
	for(i = 0; i < 16; i++) {
		/* If we're expecting the VGA format, multiply the color values appropriately. */
		palette[i].r = PALETTE_CGA[i * 3];
		palette[i].g = PALETTE_CGA[i * 3 + 1];
		palette[i].b = PALETTE_CGA[i * 3 + 2];
	}
}

int console_init(const char *title, short width, short height, int scale,
                 SDL_bool double_width, SDL_bool enable_blink, short blink_rate) {
	int render_width, render_height, x, y;

	/* Load the resources first, since the charset is required to determine the window height. */
	console_load_charset_cp437();
	console_load_palette_cga();

	console_width = width;
	console_height = height;
	console_scale = scale;
	console_double_width = double_width;
	console_blink = enable_blink;
	console_blink_rate = blink_rate;

	lprint(INFO, "Initializing console (%ix%i size, %ix%i charset, %ix%i pixmap, double width: %i, %ix scale).",
		console_width, console_height, font_width, font_height, console_width * font_width,
		console_height * font_height, (int)console_double_width, console_scale);
	console = malloc(sizeof(console_char_t) * console_width * console_height);

	/* The console should be initialized with spaces (0x20) with the color 0x07 in order
	   to better emulate the real thing. */
	for(y = 0; y < console_height; y++) {
		for(x = 0; x < console_width; x++) {
			console_char_t *cell = &CONSOLE(x, y);

			cell->ch = 0x20;
			cell->col = 0x07;
		}
	}

	render_width = console_width * font_width;
	render_height = console_height * font_height;

	video_init(title, render_width, render_height,
	           render_width * console_scale * (console_double_width ? 2 : 1),
	           render_height * console_scale);
}

void console_update() {
	int x, y;
	console_char_t *cell;
	Uint8 *glyph;

	console_blink_timer += 1;
	if(console_blink_timer >= console_blink_rate) {
		console_blink_state = !console_blink_state;
		console_blink_timer = 0;
	}

	for(y = 0; y < console_height; y++) {
		for(x = 0; x < console_width; x++) {
			palette_color_t *bg_color, *fg_color;
			int ch_x, ch_y;

			cell = &CONSOLE(x, y);
			glyph = &charset[cell->ch * font_height];

			/* Determine character color. If blink is enabled, blocks with the highest
			   bit set should have blinking foregrounds. */
			if(console_blink && cell->col >= 0x80) {
				bg_color = &palette[(cell->col >> 4) & 0x07];
				fg_color = console_blink_state ? bg_color : &palette[cell->col & 0x0F];
			} else {
				bg_color = &palette[cell->col >> 4];
				fg_color = &palette[cell->col & 0x0F];
			}

			/* Plot the character onto the pixmap. */
			for(ch_y = 0; ch_y < font_height; ch_y++) {
				for(ch_x = 0; ch_x < font_width; ch_x++) {
					pixels[CHAR_PIXEL(x, y, ch_x, ch_y)] =
						((*(glyph + ch_y) >> (font_width - ch_x - 1)) & 0x01) == 0x01
							? PAL_ARGB(fg_color) : PAL_ARGB(bg_color);
				}
			}
		}
	}

	/* Draw the result to the screen. */
	video_update();
}
