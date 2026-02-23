#include "game_types.h"
#include "logger.h"
#include "platform.h"
#include "kmemory.h"
#include "event.h"

#include "application.h"

typedef struct application_state
{
	game_t* game_instance;
	b8 is_running;
	b8 is_suspended;
	platform_state_t* platform_state;
	i16 width;
	i16 height;
	f64 last_time;
} application_state_t;

static b8 initialized = false;
static application_state_t app_state;

KAPI b8 application_create(game_t* game_instance)
{
	if (initialized)
	{
		KERROR("application_create called more than once");

		return false;
	}

	app_state.game_instance = game_instance;

	// TODO: remove this when the logging system is complete
	KFATAL("A test message: %d", 1);
	KERROR("A test message: %d", 1);
	KWARN("A test message: %d", 1);
	KINFO("A test message: %d", 1);
	KDEBUG("A test message: %d", 1);
	KTRACE("A test message: %d", 1);


	// initialize subsystems
	initialize_logging();
	if (!event_initialize())
	{
		KFATAL("event system initialization failed. process terminated");

		return false;
	}

	app_state.is_running = true;
	app_state.is_suspended = false;

	app_state.platform_state = platform_startup(
		game_instance->config.name, 
		game_instance->config.start_pos_x,
		game_instance->config.start_pos_y,
		game_instance->config.start_width,
		game_instance->config.start_height);

	if (!app_state.platform_state)
	{
		return false;
	}


	if (!app_state.game_instance->initialize(app_state.game_instance))
	{
		KFATAL("initializing game failed");

		return false;
	}

	app_state.game_instance->on_resize(app_state.game_instance, app_state.game_instance->config.start_width, app_state.game_instance->config.start_height);

	initialized = true;

	return true;
}

KAPI b8 application_run()
{
	KINFO(memory_get_usage_str());

	while (app_state.is_running)
	{
		if (!platform_pump_messages(app_state.platform_state))
		{
			app_state.is_running = false;
		}

		if (!app_state.is_suspended)
		{
			if (!app_state.game_instance->update(app_state.game_instance, (f32)0))
			{
				KFATAL("Game update failed");
				app_state.is_running = false;
			}

			if (!app_state.game_instance->render(app_state.game_instance, (f32)0))
			{
				KFATAL("Game update failed");
				app_state.is_running = false;
			}
		}

	}

	app_state.is_running = false;

	event_shutdown();

	platform_shutdown(app_state.platform_state);

	return true;
}
