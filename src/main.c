/* main.c
 *
 * This contains the program's entry point.
 */

#include "defs.h"
#include "game.h"
#include "video.h"

/* We use the main() function to set up the video, enter the game loop, and
   shut down the video subsystem.

   If any other setup needs done, it can be put here. */
int main(int argc, char **argv) {
	/* Calls our function in video.c to initialize SDL's video subsystem and
	   create a rendering window. The definitions that are passed to the init
	   function are contained in defs.h. */
	if(video_init(PROJECT_NAME, RENDER_WIDTH, RENDER_HEIGHT, WINDOW_WIDTH,
		           WINDOW_HEIGHT) != 0) {
		/* The video subsystem did not initialize successfully. Exit with an
		   error status. */
		return 1;
	}

	/* Enters the main game loop. This will not return until the game loop is
	   broken. */
	game_loop();

	/* Closes the SDL window and cleans up its resources. */
	video_close();

	/* Cleans up SDL's resources. */
	SDL_Quit();

	/* Fin! */
	return 0;
}
