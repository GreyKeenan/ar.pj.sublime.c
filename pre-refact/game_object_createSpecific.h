#ifndef GAME_OBJECT_CREATESPECIFIC_H
#define GAME_OBJECT_CREATESPECIFIC_H

#include <stdbool.h>

#include "game_object.h"
#include "game_object_methods.h"

Game_Object Game_Object_createWater(const void* texture);
Game_Object Game_Object_createWall(const void* texture);

Game_Entity Game_Entity_createSlime(const void* texture, Game_Object *foundation, unsigned char x, unsigned char y);
Game_Entity Game_Entity_createLime(const void* texture, Game_Object *foundation, unsigned char x, unsigned char y);
Game_Entity Game_Entity_createBox(const void* texture, Game_Object *foundation, unsigned char x, unsigned char y);
//Game_Entity Game_Entity_createUnstableGround(void* texture);

#endif
