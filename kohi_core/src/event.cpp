#include "event.h"

#include "memory.h"

typedef struct registered_event
{
	void* listener;
	event_handler_t handler;
} registered_event_t;

typedef struct event_code_entry
{
	registered_event_t* event;
} event_code_entry_t;

#define EVENT_MAX_CODE 16384

typedef struct event_system_state
{
	b8 is_initialized;
	event_code_entry_t registered[EVENT_MAX_CODE];
} event_system_state_t;

static event_system_state_t state;
