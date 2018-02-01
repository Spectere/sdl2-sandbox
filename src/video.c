/* video.c
 *
 * This file handles creating, updating, and destroying the video output.
 */

#include <stdlib.h>

#include "log.h"
#include "video.h"

/* The size of the texture and window. */
int tex_width, tex_height, wnd_width, wnd_height;

/* The main pixmap. This contains the pixels that will be drawn to the
   screen. */
Uint32 *pixels;

/* The window, renderer, and texture structures used by SDL. */
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture = NULL;

/* Closes the SDL window and the video subsystem. */
void video_close() {
	lprint(INFO, "Closing video subsystem");

	/* Destroys all of the resources used by the video subsystem. This will
	   also close the window. */
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	/* Shuts down SDL's video subsystem. No video calls should be made after
	   this point unless the video subsystem is brought back up. */
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

/* Initializes the video subsystem and creates all resources necessary for
   rendering to occur. */
int video_init(const char *title, int render_width, int render_height,
               int window_width, int window_height) {
	/* Copies all of the passed variables into local variables. */
	tex_width = render_width;
	tex_height = render_height;
	wnd_width = window_width;
	wnd_height = window_height;

	/* Initializes SDL's video subsystem. This should be called before the
	   video subsystem is used. */
	SDL_Init(SDL_INIT_VIDEO);

	lprint(INFO, "Initializing video (%ix%i surface, %ix%i window)...",
		tex_width, tex_height, wnd_width, wnd_height);

	/* Creates the SDL window. This is the physical window that is displayed
	   on the user's screen. */
	lprint(DEBUG, "Creating window");
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, window_width, window_height, 0);
	if(window == NULL) {
		/* If the window variable is null, the window has not been created
		   successfully. Log the error that SDL gave us and return with an
		   error status. */
		lprint(ERROR, "Error creating window: %s", SDL_GetError());
		return 1;
	}

	/* Creates an SDL renderer. This takes an SDL texture and plots it into the
	   SDL window. First, we try to create a hardware accelerated renderer. */
	lprint(DEBUG, "Creating hardware accelerated renderer");
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == NULL) {
		/* If we make it inside of this block, we were unable to create an
		   accelerated renderer. First we log the error, then we try to create
		   a software renderer as a fallback. */
		lprint(WARN, "Failed to create hardware accelerated renderer: %s", SDL_GetError());
		lprint(WARN, "Attempting to create a software renderer");
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE | SDL_RENDERER_PRESENTVSYNC);
		if(renderer == NULL) {
			/* If we made it here, we were unable to create a software
			   renderer. Log the error and return with an error status. */
			lprint(ERROR, "Error creating renderer: %s", SDL_GetError());
			return 1;
		}
	}

	/* Creates an SDL texture with a 32-bit ARGB (alpha, red, green, blue)
	   pixel format. This contains the raw pixel data that the renderer
	   processes and sends to the video card.

	   We use a streaming texture for this, as we're going to be updating it
	   on every frame. */
	lprint(DEBUG, "Creating texture");
	texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, tex_width, tex_height);
	if(texture == NULL) {
		/* If we made it here, we were unable to create a texture. Log the
		   error and return with an error status. */
		lprint(ERROR, "Error creating texture: %s", SDL_GetError());
		return 1;
	}

	/* Initializes the pixel array. This will allow the pixel array to be used
	   to update the resulting video output. */
	pixels = malloc(sizeof(Uint32) * tex_width * tex_height);

	/* Log our success and return a normal status. */
	lprint(INFO, "Video subsystem initialized successfully");
	return 0;
}

void video_update() {
	/* Updates the texture with the values inside of the pixmap that we
	   defined. */
	SDL_UpdateTexture(texture, NULL, pixels, tex_width * sizeof(Uint32));

	/* This call clears the renderer's output before drawing the new image to
	   the screen. Since the drawing method that we're using will always fill
	   the entire screen with pixels (as opposed to using multiple textures and
	   placing those where appropriate) we never need to call this. It will
	   have no visible effect and will negatively impact performance,
	   especially if a softawre renderer is used.

	   If you do need this functionality for any reason, uncomment the line
	   below. */
	/* SDL_RenderClear(); */

	/* Copies the texture to the rendering target. While this call does allow
	   for partial updates, we don't use them for simplicity's sake--we just
	   plot the entire texture to the target. */
	SDL_RenderCopy(renderer, texture, NULL, NULL);

	/* This updates the screen with the rendering that was performed by the
	   SDL_RenderCopy() call. This is what draws the frame to the user's
	   screen. */
	SDL_RenderPresent(renderer);
}
