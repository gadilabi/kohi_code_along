#include "event.h"
#include "kmemory.h"
#include "logger.h"
#include "assert.h"

#include "input.h"

typedef struct keyboard_state
{
	b8 keys[256];
} keyboard_state_t;

typedef struct mouse_state
{
	i16 x;
	i16 y;
	b8 buttons[BUTTON_MAX_BUTTONS];
} mouse_state_t;

typedef struct input_state
{
	keyboard_state keyboard_current;
	keyboard_state keyboard_previous;
	mouse_state mouse_current;
	mouse_state mouse_previous;
} input_state_t;

static b8 is_initialize = false;
static input_state state = {};

void input_initialize()
{
	memory_zero(&state, sizeof(input_state_t));
	is_initialize = true;
	KINFO("Input subsystem initialized");
}

void input_shutdown()
{
	// TODO : add shutdown routines when needed
	is_initialize = false;
}

void input_update(f64 delta_time)
{
	if (!is_initialize)
	{
		return;
	}

	memory_copy(&state.keyboard_previous, &state.keyboard_current, sizeof(keyboard_state_t));
	memory_copy(&state.mouse_previous, &state.mouse_current, sizeof(mouse_state_t));
}

void input_process_key(key_t key, b8 is_pressed)
{
	if (state.keyboard_current.keys[key] != is_pressed)
	{
		state.keyboard_current.keys[key] = is_pressed;

		event_context_t ctx;
		ctx.data.u16[0] = key;
		event_fire(is_pressed ? EVENT_CODE_KEY_PRESSED : EVENT_CODE_KEY_RELEASED, NULL, ctx);
	}
}

void input_process_button(button_t btn, b8 is_pressed)
{
	if (state.mouse_current.buttons[btn] != is_pressed)
	{
		state.mouse_current.buttons[btn] = is_pressed;

		event_context_t ctx;
		ctx.data.u16[0] = btn;
		event_fire(is_pressed ? EVENT_CODE_BUTTON_PRESSED : EVENT_CODE_BUTTON_RELEASED, NULL, ctx);
	}
}

void input_process_mouse_move(i16 x, i16 y)
{
	if (state.mouse_current.x != x || state.mouse_current.y != y)
	{
		KDEBUG("mouse move event fired %d %d \n", x, y);

		state.mouse_current.x = x;
		state.mouse_current.y = y;

		event_context_t ctx;
		ctx.data.u16[0] = x;
		ctx.data.u16[1] = y;
		event_fire(EVENT_CODE_MOUSE_MOVED, NULL, ctx);
	}
}

void input_process_mouse_wheel(i8 z_delta)
{
	event_context_t ctx;
	ctx.data.u8[0] = z_delta;
	event_fire(EVENT_CODE_MOUSE_WHEEL, NULL, ctx);
}

b8 input_is_keydown(key_t key)
{
	KASSERT(is_initialize);

	return state.keyboard_current.keys[key] == 1;
}

b8 input_is_keyup(key_t key)
{
	KASSERT(is_initialize);

	return state.keyboard_current.keys[key] == 0;
}

KAPI b8 input_was_keyup(key_t key)
{
	KASSERT(is_initialize);

	return state.keyboard_previous.keys[key] == 1;
}

KAPI b8 input_was_keydown(key_t key)
{
	KASSERT(is_initialize);

	return state.keyboard_previous.keys[key] == 0;
}

KAPI b8 input_is_button_down(button_t btn)
{
	KASSERT(is_initialize);

	return state.mouse_current.buttons[btn] == 1;
}

KAPI b8 input_is_button_up(button_t btn)
{
	KASSERT(is_initialize);

	return state.mouse_current.buttons[btn] == 0;
}

KAPI b8 input_was_button_down(button_t btn)
{
	KASSERT(is_initialize);

	return state.mouse_previous.buttons[btn] == 1;
}

KAPI b8 input_was_button_up(button_t btn)
{
	KASSERT(is_initialize);

	return state.mouse_previous.buttons[btn] == 0;
}

KAPI b8 input_get_mouse_position(i32* x, i32* y)
{
	KASSERT(is_initialize);

	if (x == NULL || y == NULL)
	{
		return false;
	}

	*x = state.mouse_current.x;
	*y = state.mouse_current.y;

	return true;
}

KAPI b8 input_get_previous_mouse_position(i32* x, i32* y)
{
	KASSERT(is_initialize);

	if (x == NULL || y == NULL)
	{
		return false;
	}

	*x = state.mouse_previous.x;
	*y = state.mouse_previous.y;

	return true;
}
