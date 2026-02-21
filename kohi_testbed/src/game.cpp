#include "defines.h"
#include "game.h"
#include "logger.h"
#include "game_types.h"

b8 game_start(game_t* game)
{
	KDEBUG("game start");
	return true;
}

b8 game_update(game_t* game, f32 delta_time)
{
	return true;
}

b8 game_render(game_t* game, f32 delta_time)
{
	return true;
}

void game_on_resize(game_t* game, u32 width, u32 height)
{
}
