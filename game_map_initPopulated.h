#ifndef GAME_MAP_POPULATE_H
#define GAME_MAP_POPULATE_H

#include "rendering.h"

#include "game_map_forw.h"

#include "game_tile_forw.h"

Game_Map *Game_Map_initPopulated(const char* path, Game_Tile **gameTiles, const RenderingT_texture **entityTextures);


#endif
