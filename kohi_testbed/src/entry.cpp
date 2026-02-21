#include "game_types.h"
#include "entry.h"
#include "game.h"

#include "kmemory.h"

b8 game_initialize(game_t* out_game)
{
	out_game->config.start_pos_x = 100;
	out_game->config.start_pos_y = 100;
	out_game->config.start_width = 1200;
	out_game->config.start_height = 720;
	out_game->config.name = "kohi testbed";

	out_game->initialize = &game_start;
	out_game->update = &game_update;
	out_game->render = &game_render;
	out_game->on_resize = &game_on_resize;

	out_game->state = memory_allocate(sizeof(game_state_t), MEMORY_TAG_GAME);

	return true;
}


