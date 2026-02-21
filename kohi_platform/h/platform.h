#pragma once


#include "defines.h"

typedef struct platform_state platform_state_t;


platform_state* platform_startup(
	const char* app_name,
	int32_t x,
	int32_t y,
	int32_t width,
	int32_t	height);

void platform_shutdown(platform_state* state);

b8 platform_pump_messages(platform_state* state);

void* platform_allocate(u64 size, b8 aligned);
void platform_free(void* block, bool aligned);
void* platform_zero_memory(void* block, u64 size);
void* platform_copy_memory(void* dst, const void* src, u64 size);
void* platform_set_memory(void* dst, char value, u64 size);

void platform_console_write(const char* msg, u8 color);
void platform_console_write_error(const char* msg, u8 color);

f64 platform_get_absolute_time();
void platform_sleep(u64 ms);
