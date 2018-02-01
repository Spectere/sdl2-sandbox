/* event.c
 *
 * This file handles all input events that occur in the game loop.
 */

#include <SDL.h>

#include "event.h"

/* This function handles keyboard input events. */
event_result_t event_keyboard(const SDL_Event e) {
	SDL_KeyboardEvent kb = e.key;

	/* Handle key up events. */
	if(kb.type == SDL_KEYUP) {
		switch(kb.keysym.sym) {
		/* If escape is pressed, send a quit message to the game loop. */
		case SDLK_ESCAPE:
			return EV_QUIT;
		}
	}

	return EV_NONE;
}

/* This function handles mouse button click events. */
event_result_t event_mouse_button(const SDL_Event e) {
	SDL_MouseButtonEvent btn = e.button;

	/* Mouse button events are not handled by the sample project. Place your
	   code here. */

	return EV_NONE;
}

/* This function handles mouse scroll wheel events. */
event_result_t event_mouse_wheel(const SDL_Event e) {
	SDL_MouseWheelEvent wheel = e.wheel;

	/* Mouse wheel events are not handled by the sample project. Place your
	   code here. */

	return EV_NONE;
}

/* This function handles mouse motion events. */
event_result_t event_mouse_motion(const SDL_Event e) {
	SDL_MouseMotionEvent motion = e.motion;

	/* Mouse motion is not handled by the sample project. Place your code
	   here. */

	return EV_NONE;
}

/* This function handles window events (moving, resizing, minimizing, etc). */
event_result_t event_window(const SDL_Event e) {
	SDL_WindowEvent wnd = e.window;
	return EV_NONE;
}

/* This function is called by the game loop to check the input events and
   dispatch it to the appropriate handlers. The input is either handled by
   the input manager or, if it's a code that affects the core game loop, is
   passed back to it via the event_result_t enumeration (see event.h for its
   definition). */
event_result_t event_process() {
	SDL_Event e;
	SDL_PollEvent(&e);

	/* Calls the appropriate handler for each supported event type. */
	switch(e.type) {
	/* Keypress event. */
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		return event_keyboard(e);

	/* Mouse button event. */
	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
		return event_mouse_button(e);

	/* Mouse wheel event. */
	case SDL_MOUSEWHEEL:
		return event_mouse_wheel(e);

	/* Mouse motion event. */
	case SDL_MOUSEMOTION:
		return event_mouse_motion(e);

	/* Window event. */
	case SDL_WINDOWEVENT:
		return event_window(e);

	/* If a quit event is found (the main windows is closed, the window manager
	   tells us to quit, etc), send a quit message to the game loop. */
	case SDL_QUIT:
		return EV_QUIT;
	}

	/* No recognizable event occurred. */
	return EV_NONE;
}
