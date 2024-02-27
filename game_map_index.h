#ifndef GAME_MAP_INDEX_H
#define GAME_MAP_INDEX_H

#include <stdbool.h>

#include "game_map_forw.h"

#include "game_map_tileI.h"

bool Game_Map_isInBounds(const Game_Map *self, unsigned char x, unsigned char y);

Game_Map_TileI *Game_Map_getIndex(const Game_Map *self, unsigned char x, unsigned char y);
void Game_Map_setIndex(Game_Map *self, unsigned char x, unsigned char y, Game_Map_TileI *to);

#endif
