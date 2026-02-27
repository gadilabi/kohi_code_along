#pragma once

#include "defines.h"

typedef struct event_context
{
	union
	{
		i64 i64[2];
		u64 u64[2];
		f64 f64[2];

		i32 i32[4];
		u32 u32[4];
		f32 f32[4];

		i16 i16[8];
		u16 u16[8];

		i8 i8[16];
		u8 u8[16];

		char c[16];
	} data;
} event_context_t;

// return true if handled
typedef b8(*event_handler_t)(u16 code, void* sender, void* listener, event_context_t ctx);

b8 event_initialize();
void event_shutdown();

/*
Register to events sent with the given code.
events with duplicate listener/cb combos will be ignored an false to be returned.
@param code The even code to listen for
@param listener a pointer to a listener instance, can be NULL
@param cb the function to be invoked when the event code is fired
@return true if the event successfully registerd, otherwise false
*/
KAPI b8 event_register(u16 code, void* listener, event_handler_t cb);

KAPI b8 event_unregister(u16 code, void* listener, event_handler_t cb);

KAPI b8 event_fire(u16 code, void* sender, event_context_t ctx);

typedef enum event_system_code
{
	// shuts the application on the next frame
	EVENT_CODE_APPLICATION_QUIT = 0x01,

	// key_code = u16[0]
	EVENT_CODE_KEY_PRESSED = 0x02,

	// key_code = u16[0]
	EVENT_CODE_KEY_RELEASED = 0x03,

	// key_code = u16[0]
	EVENT_CODE_BUTTON_PRESSED = 0x04,

	// key_code = u16[0]
	EVENT_CODE_BUTTON_RELEASED = 0x05,

	// x = u16[0]
	// y = u16[1]
	EVENT_CODE_MOUSE_MOVED = 0x06,

	// z_delta = u8[0]
	EVENT_CODE_MOUSE_WHEEL = 0x07,

	// width = u16[0]
	// height = u16[1]
	EVEN_CODE_RESIZED = 0x08,

	EVENT_MAX_SYSTEM_CODE = 0xFF

} event_system_code_t;
