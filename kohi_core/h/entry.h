#pragma once

#include "application.h"
#include "logger.h"
#include "kmemory.h"
#include "game_types.h"

b8 game_initialize(game_t* out_game);

int main(void)
{

	memory_initialize();

	game_t game_instance;

	if (!game_initialize(&game_instance))
	{
		KFATAL("create_game failed");

		return -1;
	}

	if (!game_instance.initialize || !game_instance.on_resize || !game_instance.render || !game_instance.update)
	{
		KFATAL("The game function pointers must all be assigned");

		return -2;
	}

	game_config_t config;
	config.name = (char*)"test app";
	config.start_pos_x = 100;
	config.start_pos_y = 100;
	config.start_width = 920;
	config.start_height = 920;

	if (!application_create(&game_instance))
	{
		KFATAL("failed to create application");

		return -1;
	}

	if (!application_run())
	{
		KFATAL("application did not manage to run");

		return -1;
	}

	memory_shutdown();

	return 0;
}
