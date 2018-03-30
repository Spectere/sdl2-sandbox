/* game.c - Main game loop. */

#include <SDL.h>

#include "console.h"
#include "defs.h"
#include "event.h"

void game_loop() {
	event_result_t ev = EV_NONE;
	SDL_bool running = SDL_TRUE;

	while(running) {
		Uint8 i = 0;
		int x, y;

		ev = event_process();

		switch(ev) {
		case EV_QUIT:
			running = SDL_FALSE;
			break;
		}

		for(y = 0; y < CONSOLE_HEIGHT; y++) {
			for(x = 0; x < CONSOLE_WIDTH; x++) {
				CONSOLE(x, y).ch = i;
				CONSOLE(x, y).col = i++;
			}
		}

		console_update();
	}
}
