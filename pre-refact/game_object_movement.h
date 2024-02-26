#ifndef GAME_OBJECT_MOVEMENT_H
#define GAME_OBJECT_MOVEMENT_H

#include "game_object.h"

#include "game_map.h"
#include "game_map_access.h"

void Game_Entity_move(Game_Entity *self, Game_Map *map, unsigned char toX, unsigned char toY);



#endif
