#ifndef GAME_MAP_POPULATE_H
#define GAME_MAP_POPULATE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "game_map.h"
#include "game_map_access.h"

#include "game_object.h"
#include "game_object_specificInitializers.h"

Game_Map Game_Map_initializePopulated(const char* path, const Game_Object *staticGameObjects, const void **gameEntityTextures);


#endif
