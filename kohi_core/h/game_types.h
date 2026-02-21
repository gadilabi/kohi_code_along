#pragma once

#include "defines.h"

typedef struct game_config
{
	i16 start_pos_x;
	i16 start_pos_y;
	i16 start_width;
	i16 start_height;
	const char* name;
} game_config_t;

typedef struct game
{
	game_config_t config;
	b8 (*initialize)(struct game* game_instance);
	b8 (*update)(struct game* game_instance, f32 delta_time);
	b8 (*render)(struct game* game_instance, f32 delta_time);
	void (*on_resize)(struct game* game_instance, u32 width, u32 height);

	void* state;

} game_t;

