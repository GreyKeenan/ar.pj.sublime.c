#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include "game_map_forw.h"
#include "game_map_tileI_forw.h"

typedef struct Game_Level {
	
	Game_Map *map;

	Game_Map_TileI **players;
	Game_Map_TileI **limes;
	Game_Map_TileI **uniqueTiles;

	unsigned char playerCount;
	unsigned char limeCount;
	unsigned char uniqueTileCount;

} Game_Level;

Game_Level *Game_Level_init(const char *path, Game_Map_TileI **tiles);
void Game_Level_destroy(Game_Level *self);

#endif
