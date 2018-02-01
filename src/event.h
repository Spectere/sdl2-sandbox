/* event.h
 *
 * This header file contains public structures and functions related to the
 * game's event handler.
 */

/* Include guard to ensure that this file is only included once. */
#ifndef _EVENT_H_
#define _EVENT_H_

/* This enumeration contains all valid values that the input system can return
   to the main game loop. */
typedef enum {
	/* The game loop doesn't need to handle anything special. */
	EV_NONE,

	/* The game loop is being instructed to clean up and exit. */
	EV_QUIT
} event_result_t;

/* Processes input events. This is called by the main game loop. */
event_result_t event_process();

#endif /* _EVENT_H_ */
