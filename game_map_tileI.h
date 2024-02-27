#ifndef GAME_MAP_TILEI_H
#define GAME_MAP_TILEI_H

#include <stdbool.h>

#include "renderingT.h"
#include "game_map_tileI_forw.h"

typedef bool Game_Map_TileI_onPushF (Game_Map_TileI *self, char directionX, char directionY);
typedef void Game_Map_TileI_onEnterF (Game_Map_TileI *self, Game_Map_TileI *other);
typedef void Game_Map_TileI_onExitF (Game_Map_TileI *self, Game_Map_TileI *other);

typedef struct Game_Map_TileI {

	Game_Map_TileI *foundation;
	RenderingT_texture *texture;

	Game_Map_TileI_onPushF *onPush;
	Game_Map_TileI_onEnterF *onEnter;
	Game_Map_TileI_onExitF *onExit;
	
} Game_Map_TileI;

#endif
