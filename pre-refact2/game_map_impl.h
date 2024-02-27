#ifndef GAME_MAP_IMPL_H
#define GAME_MAP_IMPL_H

#include "game_tile_forw.h"
#include "game_entity_forw.h"
#include "game_player_forw.h"

typedef struct Game_Map {
	Game_Tile **grid;
	Game_Tile **uniqueTiles;
	Game_Player **players;
	unsigned char width;
	unsigned char height;
	unsigned char playerCount;
} Game_Map;

Game_Map *Game_Map_init(unsigned char width, unsigned char height, unsigned char playerCount);
void Game_Map_destroy(Game_Map *self);

#endif
