#pragma once

#include "defines.h"

#define LOG_WARN_ENABLE 1
#define LOG_INFO_ENABLE 1
#define LOG_DEBUG_ENABLE 1
#define LOG_TRACE_ENABLE 1

#if KRELEASE == 1
#define LOG_DEBUG_ENABLE 0
#define LOG_TRACE_ENABLE 0
#endif

enum log_level
{
	LOG_LEVEL_FATAL = 0,
	LOG_LEVEL_ERROR,
	LOG_LEVEL_WARN,
	LOG_LEVEL_INFO,
	LOG_LEVEL_DEBUG,
	LOG_LEVEL_TRACE
};

bool initialize_logging();
void shutdown_logging();

KAPI void log_output(log_level level, const char* msg, ...);
#define KFATAL(msg, ...) log_output(LOG_LEVEL_FATAL, msg, ##__VA_ARGS__);

#ifndef KERROR
#define KERROR(msg, ...) log_output(LOG_LEVEL_ERROR, msg, ##__VA_ARGS__);
#endif

#if LOG_WARN_ENABLE == 1
#define KWARN(msg, ...) log_output(LOG_LEVEL_WARN, msg, ##__VA_ARGS__);
#else
#define KWARN(msg, ...)
#endif

#if LOG_INFO_ENABLE == 1
#define KINFO(msg, ...) log_output(LOG_LEVEL_INFO, msg, ##__VA_ARGS__);
#else
#define KINFO(msg, ...)
#endif

#if LOG_DEBUG_ENABLE == 1
#define KDEBUG(msg, ...) log_output(LOG_LEVEL_DEBUG, msg, ##__VA_ARGS__);
#else
#define KDEBUG(msg, ...)
#endif

#if LOG_TRACE_ENABLE == 1
#define KTRACE(msg, ...) log_output(LOG_LEVEL_TRACE, msg, ##__VA_ARGS__);
#else
#define KTRACE(msg, ...)
#endif
