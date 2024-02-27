
#include <stdlib.h>

#include "game_tile_impl.h"

Game_Tile *Game_Tile_init(RenderingT_texture *texture, Game_Tile *foundation, Game_TileT_fOnPush onPush, Game_TileT_fOnExit onExit) {
	Game_Tile *self = malloc(sizeof(Game_Tile));

	self->texture = texture;
	self->foundation = foundation;
	self->onPush = onPush;
	self->onExit = onExit;

	return self;
}
void Game_Tile_destroy(Game_Tile *self) {
	free(self);
}
