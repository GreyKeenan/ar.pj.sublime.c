#ifndef GAME_MAP_ACCESS_H
#define GAME_MAP_ACCESS_H

#include <stdio.h>
#include <stdbool.h>

#include "game_map.h"

#include "game_object.h"

bool Game_Map_isInBounds(const Game_Map *self, const unsigned char x, const unsigned char y);

Game_Object *Game_Map_index(const Game_Map *self, const unsigned char x, const unsigned char y);
void Game_Map_setIndex(Game_Map *self, const unsigned char x, const unsigned char y, const Game_Object *to);


#endif
