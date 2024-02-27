
#include "game_tile_empty.h"

#include <stdlib.h>

Game_Map_TileI *Game_Tile_Empty_initWithTexture(RenderingT_texture *texture) {
	Game_Map_TileI *self = malloc(sizeof(Game_Map_TileI *));
	
	self->texture = texture;
	self->foundation = NULL;

	self->onPush = NULL;
	self->onEnter = NULL;
	self->onExit = NULL;

	return self;
}
