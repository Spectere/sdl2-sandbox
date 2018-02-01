/* video.h
 *
 * This header exposes all of the public functions related to the video
 * subsystem.
 */

/* Include guard to ensure that this file is only included once. */
#ifndef _VIDEO_H_
#define _VIDEO_H_

#include <SDL.h>
#include "defs.h"

/* This macro calculates a 32-bit pixel value based on the specified RGB
   values (valid values are 0-255). This should be used when updating the
   pixmap. */
#define RGB(r, g, b) (0xFF000000 | (r << 16) | (g << 8) | b)

/* This macro translates (x, y) coordinates to the appropriate position on the
   pixmap. Please note that no bounds checking is performed, so be sure that
   the values that you use are positive and less than RENDER_WIDTH and
   RENDER_HEIGHT.

   For example, if you wanted to update a single pixel to red, you could use
   the following call:

       pixels[POS(10, 5)] = RGB(255, 0, 0);
*/
#define POS(x, y) ((RENDER_WIDTH * y) + x)

/* This is the pixmap that is created when the video subsystem is initialized.
   For simplicity's sake, this can be updated by any file that includes
   video.h. */
extern Uint32 *pixels;

/* This function closes the video subsystem. This should be called before the
   program terminates. */
void video_close();

/* This function initializes the video subsystem. This must be called before
   the video_update() function is called or the pixmap is updated.

   Parameters:
       - title: sets the window title
       - render_width/render_height: sets the size of the pixmap.
       - window_width/window_height: sets the size of the window. SDL will
         automatically scale the output accordingly. Setting this to a a value
         that's evenly divisible by render_width/render_height is highly
         recommended. */
int video_init(const char *title, int render_width, int render_height,
               int window_width, int window_height);

/* Updates the texture that's used by the renderer and displays it to the
   screen. This must be called after each frame is drawn to display the results
   to the screen. */
void video_update();

#endif /* _VIDEO_H_ */
