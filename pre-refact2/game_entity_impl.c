
#include <stdlib.h>

#include "game_entity_impl.h"

Game_Entity *Game_Entity_init(RenderingT_texture *texture, Game_TileT_fOnPush onPush, Game_TileT_fOnExit onExit, Game_Tile *foundation, unsigned char x, unsigned char y) {
	Game_Entity *self = malloc(sizeof(Game_Entity));

	self->gameTile.texture = texture;
	self->gameTile.onPush = onPush;
	self->gameTile.onExit = onExit;

	self->foundation = foundation;
	self->x = x;
	self->y = y;

	return self;
}
void Game_Entity_destroy(Game_Entity *self) {
	free(self);
}
