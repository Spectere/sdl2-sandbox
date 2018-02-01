/* game.c - Main game loop. */

#include <SDL.h>

#include "defs.h"
#include "event.h"
#include "video.h"

void game_loop() {
	event_result_t ev = EV_NONE;
	SDL_bool running = SDL_TRUE;

	Uint8 r = 0, g = 64, b = 128;
	int i;

	while(running) {
		ev = event_process();

		switch(ev) {
		case EV_QUIT:
			running = SDL_FALSE;
			break;
		}

		/* Replace this with something niftier. :) */
		r++; g--; b;
		for(i = 0; i < RENDER_WIDTH * RENDER_HEIGHT; i++) {
			pixels[i] = RGB(r++, g++, b++);
		}

		video_update();
	}
}
