/* game.c
 *
 * This file contains the main game loop and related structures.
 */

#include <SDL.h>

#include "defs.h"
#include "event.h"
#include "video.h"

/* The main game loop. This is called by the main() function. */
void game_loop() {
	/* This variable contains events that are passed to the game loop by the
	   input system. */
	event_result_t ev = EV_NONE;

	/* This variable indicates whether or not the game loop should continue
	   running. If it is set to SDL_FALSE, the game loop will end. */
	SDL_bool running = SDL_TRUE;

	/* These are variables used by the sample video output. Delete these and
	   replace them with your own! :) */
	Uint8 r = 0, g = 64, b = 128;
	int i;

	/* The game loop. This calls all of the functions necessary to update the
	   scene and display it on screen. */
	while(running) {
		/* This calls the event/input system. */
		ev = event_process();

		/* This handles all relevant return values from the input system. */
		switch(ev) {
		case EV_QUIT:
			/* A quit message was received, so we'll set the game loop to
			   stop running after this cycle. */
			running = SDL_FALSE;
			break;
		}

		/* Create a slightly trippy effect just to show that
		   everything's working. :)

		   Replace this with your own drawing routines. */
		r++; g--; b;
		for(i = 0; i < RENDER_WIDTH * RENDER_HEIGHT; i++) {
			pixels[i] = RGB(r++, g++, b++);
		}

		/* Updates the onscreen buffer with what we just plotted. */
		video_update();
	}
}
