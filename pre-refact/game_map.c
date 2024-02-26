
#include "game_map.h"


void Game_Map_destroy(Game_Map *self) {
	free(self->grid);
	self->grid = NULL;
	free(self->entities);
	self->entities = NULL;
}

