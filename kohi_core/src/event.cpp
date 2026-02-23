#include "event.h"

#include "kmemory.h"
#include "darray.h"
#include "assert.h"

#define EVENT_MAX_CODE 16384
#define REGISTER_EVENTS_CAPACITY 4

typedef struct registered_event
{
	void* listener;
	event_handler_t handler;
} registered_event_t;

typedef struct event_code_entry
{
	darray_t* registered_events;
} event_code_entry_t;

typedef struct event_system_state
{
	event_code_entry_t registered[EVENT_MAX_CODE];
} event_system_state_t;

static b8 is_initialized = false;
static event_system_state_t state;

b8 event_initialize()
{
	if (is_initialized)
	{
		return false;
	}

	is_initialized = true;
	memory_zero(&state, sizeof(state));

	return true;
}

void event_shutdown()
{
	for (u64 i = 0; i < EVENT_MAX_CODE; ++i)
	{
		if (state.registered[i].registered_events != NULL)
		{
			darray_destroy(state.registered[i].registered_events);
		}
	}
}

KAPI b8 event_register(u16 code, void* listener, event_handler_t cb)
{
	KASSERT(is_initialized, "event system must be initialized before events can be registerd");
	KASSERT(code < EVENT_MAX_CODE, "code must be under EVENT_MAX_CODE");

	darray_t* events = state.registered[code].registered_events;

	if (events != NULL)
	{
		state.registered[code].registered_events = darray_create(REGISTER_EVENTS_CAPACITY, sizeof(registered_event_t));
	}

	u64 size = darray_size(events);
	for (u64 i = 0; i < size; ++i)
	{
		registered_event_t event;
		darray_get(events, i, &event);

		if (event.listener == listener && event.handler == cb)
		{
			return false;
		}
	}

	registered_event_t event = { .listener = listener, .handler = cb };
	if (!darray_push(state.registered[code].registered_events, &event))
	{
		return false;
	}

	return true;
}

KAPI b8 event_unregister(u16 code, void* listener, event_handler_t cb)
{
	KASSERT(is_initialized, "event system must be initialized before events can be registerd");
	KASSERT(code < EVENT_MAX_CODE, "code must be under EVENT_MAX_CODE");

	darray_t* events = state.registered[code].registered_events;

	if (events == NULL)
	{
		return false;
	}

	u64 i = 0;
	registered_event_t event;
	u64 size = darray_size(events);
	for (; i < size; ++i)
	{
		darray_get(events, i, &event);
		if (event.listener == listener && event.handler == cb)
		{
			darray_pop_at(events, i, NULL);
			break;
		}
	}

	return (i != size);
}

KAPI b8 event_fire(u16 code, void* sender, event_context_t ctx)
{
	darray_t* events = state.registered[code].registered_events;
	u64 size = darray_size(events);

	for (u64 i = 0; i < size; ++i)
	{
		registered_event_t event;
		darray_get(events, i, &event);
		event.handler(code, sender, event.listener, ctx);
	}

	return true;

}


