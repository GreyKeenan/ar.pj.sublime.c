#ifndef GAME_TILE_IMPL_H
#define GAME_TILE_IMPL_H

#include <stdbool.h>

#include "rendering.h"

#include "game_map_forw.h"
#include "game_tile_forw.h"

typedef bool(*Game_TileT_fOnPush)(Game_Tile *, Game_Map *, char, char);
typedef void(*Game_TileT_fOnExit)(Game_Tile *);

typedef struct Game_Tile {
	RenderingT_texture *texture;
	
	Game_Tile *foundation;

	Game_TileT_fOnPush onPush;
	Game_TileT_fOnExit onExit;
} Game_Tile;

Game_Tile *Game_Tile_init(RenderingT_texture *texture, Game_Tile *foundation, Game_TileT_fOnPush onPush, Game_TileT_fOnExit onExit);
void Game_Tile_destroy(Game_Tile *self);

#endif
