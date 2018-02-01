/* log.c
 *
 * This file contains the project's console logging functionality. This is
 * quite a bit simpler to use than SDL's logging subsystem and supports visible
 * severity tagging with much less fuss, but is less portable. If you plan to
 * release your project to the masses, you should consider switching to a
 * different logging system.
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "defs.h"
#include "log.h"

/* This function is the main log print function. It accepts a log
   level/severity, a format string, and a variable number of parameters to
   build the final output. The format string uses the same syntax as printf.

   All output is directed to stderr/stdout. */
void lprint(log_level_t level, const char *format, ...) {
	/* This character array will contain the adjusted format that we'll pass to
	   vfprintf. We don't need to initialize this, as strcpy will  */
	char output_format[LOG_LEN];

	/* Initializes the vararg list to prepare for future vfprintf calls. */
	va_list args;
	va_start(args, format);

	/* Ensures that adding the severity tag and a newline to the format string
	   will not cause a buffer overflow. If this occurs, print an error and
	   print the log entry without the severity tag. */
	if(strlen(format) + 10 > LOG_LEN) {
		fprintf(stderr, "[!!!] Log string is too long!\n");
		vfprintf(stdout, format, args);

		/* Normally we concatenate a newline to the format string. Since we're
		   struggling for space we'll have to print it manually. */
		fprintf(stdout, "\n");

		/* Ends the vararg list and returns to the calling function. */
		va_end(args);
		return;
	}

	/* Selects which prefix to add to the output format string. If you would
	   like to add additional log levels, add them to the log_level_t enum in
	   log.h and insert the tag here. Please note that you may have to adjust
	   the buffer overflow check above if your tag longer than the ones
	   below. */
	switch(level) {
	case DEBUG:
		strcpy(output_format, "[DEBUG] ");
		break;
	case INFO:
		strcpy(output_format, "[INFO] ");
		break;
	case WARN:
		strcpy(output_format, "[WARN] ");
		break;
	case ERROR:
		strcpy(output_format, "[ERROR] ");
		break;
	default:
		/* Since no valid severity has been passed, we'll need to initialize
		   the string so that we don't run into issues. */
		strcpy(output_format, "");
		break;
	}

	/* Concatenate the passed format string as well as a newline to the output
	   format. */
	strcat(output_format, format);
	strcat(output_format, "\n");

	/* If the severity is high enough, output to stderr instead of stdout. */
	if(level == ERROR)
		vfprintf(stderr, output_format, args);
	else
		vfprintf(stdout, output_format, args);

	/* Ends the vararg list. */
	va_end(args);
}
