/* console.h - VGA console emulation. */

#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include <SDL.h>

#define CONSOLE(console_x, console_y) console[((console_y) * console_width) + (console_x)]

typedef struct {
	Uint8 ch;
	Uint8 col;
} console_char_t;

extern console_char_t *console;
extern int console_width, console_height;

void console_close();
void console_load_charset_cp437();
void console_load_palette_cga();
int console_init(const char *title, short width, short height, int scale,
                 SDL_bool double_width, SDL_bool enable_blink, short blink_rate);
void console_update();

#endif /* _CONSOLE_H_ */
