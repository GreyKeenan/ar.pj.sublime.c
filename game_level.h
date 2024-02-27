#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include "game_map_forw.h"

typedef struct Game_Level {
	Game_Map *map;

	unsigned char playerCount;
	unsigned char limeCount;
} Game_Level;

Game_Level *Game_Level_initFromPath(const char* path);

void Game_Level_destroy(Game_Level *self);

#endif
