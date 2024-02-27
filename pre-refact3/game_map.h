#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "game_map_tileI_forw.h"

typedef struct Game_Map {
	Game_Map_TileI **grid;
	const unsigned char width;
	const unsigned char height;
} Game_Map;

Game_Map *Game_Map_init(unsigned char width, unsigned char height);
void Game_Map_destroy(Game_Map *self);

#endif
