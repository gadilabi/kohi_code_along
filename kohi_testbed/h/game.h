#pragma once

#include "defines.h"
#include "game_types.h"

typedef struct game_state
{
	f32 delta_time;
} game_state_t;

b8 game_start(game_t* game);
b8 game_update(game_t* game, f32 delta_time);
b8 game_render(game_t* game, f32 delta_time);
void game_on_resize(game_t* game, u32 width, u32 height);
