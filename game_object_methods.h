#ifndef GAME_OBJECT_METHODS_H
#define GAME_OBJECT_METHODS_H

#include "game_object.h"
#include "game_object_movement.h"

#include "game_map.h"
#include "game_map_access.h"

bool Game_Object_onPushDefault(Game_Object *self, void *_, char __, char ___);
void Game_Object_onExitDefault(Game_Object *self);

bool Game_Entity_onPushPushable(Game_Object *self, void *map, char directionX, char directionY);

#endif
