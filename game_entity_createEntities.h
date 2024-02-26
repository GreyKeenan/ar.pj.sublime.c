#ifndef GAME_ENTITY_CREATEENTITIES_H
#define GAME_ENTITY_CREATEENTITIES_H

#include "rendering.h"

#include "game_tile_forw.h"
#include "game_entity_forw.h"

Game_Entity *Game_Entity_createSlime(RenderingT_texture *texture, Game_Tile *foundation, unsigned char x, unsigned char y);
Game_Entity *Game_Entity_createLime(RenderingT_texture *texture, Game_Tile *foundation, unsigned char x, unsigned char y);
Game_Entity *Game_Entity_createBox(RenderingT_texture *texture, Game_Tile *foundation, unsigned char x, unsigned char y);


#endif
