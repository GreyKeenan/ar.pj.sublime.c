#ifndef GAME_TILE_CREATETILES_H
#define GAME_TILE_CREATETILES_H

#include "rendering.h"

#include "game_tile_forw.h"

Game_Tile *Game_Tile_createEmpty(RenderingT_texture *texture);
Game_Tile *Game_Tile_createWater(RenderingT_texture *texture);
Game_Tile *Game_Tile_createWall(RenderingT_texture *texture);

Game_Tile *Game_Tile_createSlime(RenderingT_texture *texture, Game_Tile *foundation);
Game_Tile *Game_Tile_createLime(RenderingT_texture *texture, Game_Tile *foundation);
Game_Tile *Game_Tile_createBox(RenderingT_texture *texture, Game_Tile *foundation);

//Game_Tile *Game_Tile_created(RenderingT_texture *texture);

#endif