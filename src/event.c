/* event.c - Event handler functions. */

#include <SDL.h>

#include "event.h"

event_result_t event_keyboard(const SDL_Event e) {
	SDL_KeyboardEvent kb = e.key;

	if(kb.type == SDL_KEYUP) {
		switch(kb.keysym.sym) {
		case SDLK_ESCAPE:
			return EV_QUIT;
		}
	}

	return EV_NONE;
}

event_result_t event_mouse_button(const SDL_Event e) {
	SDL_MouseButtonEvent btn = e.button;
	return EV_NONE;
}

event_result_t event_mouse_wheel(const SDL_Event e) {
	SDL_MouseWheelEvent wheel = e.wheel;
	return EV_NONE;
}

event_result_t event_mouse_motion(const SDL_Event e) {
	SDL_MouseMotionEvent motion = e.motion;
	return EV_NONE;
}

event_result_t event_window(const SDL_Event e) {
	SDL_WindowEvent wnd = e.window;
	return EV_NONE;
}

/* Main event processor. */
event_result_t event_process() {
	SDL_Event e;
	SDL_PollEvent(&e);

	switch(e.type) {
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		return event_keyboard(e);

	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
		return event_mouse_button(e);

	case SDL_MOUSEWHEEL:
		return event_mouse_wheel(e);

	case SDL_MOUSEMOTION:
		return event_mouse_motion(e);

	case SDL_WINDOWEVENT:
		return event_window(e);

	case SDL_QUIT:
		return EV_QUIT;
	}

	return EV_NONE;
}
