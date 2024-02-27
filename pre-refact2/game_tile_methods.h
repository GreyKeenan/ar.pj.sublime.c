#ifndef GAME_TILE_METHODS_H
#define GAME_TILE_METHODS_H

#include <stdbool.h>

#include "game_tile_forw.h"
#include "game_map_forw.h"

bool Game_Tile_method_onPushDefault(Game_Tile *self, Game_Map *map, char directionX, char directionY);

void Game_Tile_method_onExitDefault(Game_Tile *self);

#endif
