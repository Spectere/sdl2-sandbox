/* event.h - Event handler functions. */

#ifndef _EVENT_H_
#define _EVENT_H_

/* Values that can be sent to the main game loop. */
typedef enum {
	EV_NONE,
	EV_QUIT
} event_result_t;

/* Main event processor. */
event_result_t event_process();

#endif /* _EVENT_H_ */
