#ifndef GAME_ENTITY_IMPL_H
#define GAME_ENTITY_IMPL_H

#include "game_tile_impl.h"

typedef struct Game_Entity {
	Game_Tile gameTile;
	unsigned char x;
	unsigned char y;
} Game_Entity;

Game_Entity *Game_Entity_init(RenderingT_texture *texture, Game_TileT_fOnPush onPush, Game_TileT_fOnExit onExit, Game_Tile *foundation, unsigned char x, unsigned char y);
void Game_Entity_destroy(Game_Entity *self);
	//doesnt destroy foundation

#endif
