/* main.c - Program entry point. */

#include "defs.h"
#include "game.h"
#include "video.h"

int main(int argc, char **argv) {
	if(video_init(PROJECT_NAME, RENDER_WIDTH, RENDER_HEIGHT, WINDOW_WIDTH,
		           WINDOW_HEIGHT) != 0) {
		return 1;
	}

	game_loop();

	video_close();
	SDL_Quit();

	return 0;
}
