/* main.c - Program entry point. */

#include "console.h"
#include "defs.h"
#include "game.h"

int main(int argc, char **argv) {
	if(console_init(PROJECT_NAME, CONSOLE_WIDTH, CONSOLE_HEIGHT, CONSOLE_SCALE,
	                CONSOLE_DOUBLE_WIDTH, CONSOLE_BLINK, CONSOLE_BLINK_RATE) != 0) {
		return 1;
	}

	game_loop();

	console_close();
	SDL_Quit();

	return 0;
}
