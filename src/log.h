/* log.h
 *
 * This header file contains enumerations and public functions related to the
 * logging subsystem.
 *
 * This is quite a bit simpler to use than SDL's logging subsystem and supports
 * visible severity tagging with much less fuss, but is less portable. If you
 * plan to release your project to the masses, you should consider switching to
 * a different logging system.
 */

/* Include guard to ensure that this file is only included once. */
#ifndef _LOG_H_
#define _LOG_H_

/* Recognized log severity levels. If you add additional severities, you may
   want to add tags for them in the lprint() function in log.c so that they'll
   appear in the log output. */
typedef enum {
	DEBUG,
	INFO,
	WARN,
	ERROR
} log_level_t;

/* Logs formatted output to stdout or stderr depending on the severity
   level. The format string uses the same syntax as printf. */
void lprint(log_level_t level, const char *format, ...);

#endif /* _LOG_H_ */
