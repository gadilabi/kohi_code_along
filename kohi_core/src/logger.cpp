#include "logger.h"
#include "assert.h"
#include "platform.h"

// TODO: temporary
#include <stdio.h>
#include <cstring>
#include <cstdarg>

#define MAX_MSG_LEN 32000

bool initialize_logging()
{
	return true;
}

void shutdown_logging()
{
}

KAPI void log_output(log_level level, const char* msg, ...)
{
	const char* level_msg[] = { "[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[DEBUG]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]:" };
	bool is_error = level <= LOG_LEVEL_ERROR;

	char out_buffer[MAX_MSG_LEN];

	int32_t level_msg_length = snprintf(out_buffer, MAX_MSG_LEN, "%s", level_msg[static_cast<unsigned int>(level)]);

	va_list arg_ptr;
	va_start(arg_ptr, msg);
	vsnprintf(out_buffer + level_msg_length, MAX_MSG_LEN, msg, arg_ptr);
	va_end(arg_ptr);

	if (is_error)
	{
		platform_console_write_error(out_buffer, level);
	}
	else
	{
		platform_console_write(out_buffer, level);
	}

}

void report_assertion_failure(const char* expression, const char* msg, const char* file, uint32_t line)
{
	log_output(LOG_LEVEL_FATAL, "Assertion failure: %s, message: %s, in file: %s, line %d\n", expression, msg, file, line);
}

