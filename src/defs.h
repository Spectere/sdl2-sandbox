/* defs.h
 *
 * This header file contains global definitions and constants.
 */

/* The default caption of the SDL2 window. */
#define PROJECT_NAME "SDL2 Sandbox"

/* This controls the size of the rendering area. If this is a different size
   the window, the rendered output will be scaled appropriately. */
#define RENDER_WIDTH 320
#define RENDER_HEIGHT 240

/* This controls the height of the window that appears when the program is run.
   If this is a different size than the rendering surface (specified above),
   the output will be scaled to fit. */ 
#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 720

/* This controls the maximum length of the log output, combined with the
   severity tag (i.e. "[ERROR]", "[WARN]", etc). If this value is exceeded, the
   log entry will not be printed. */
#define LOG_LEN 160
