
#include "game_map.h"

#include <stdlib.h>
#include <string.h>

Game_Map *Game_Map_init(unsigned char width, unsigned char height) {
	Game_Map *self = malloc(sizeof(Game_Map));

	Game_Map temp = {
		.width = width,
		.height = height,
		.grid = malloc(sizeof(*self->grid) * (width * height))
	};
	memcpy(self, &temp, sizeof(Game_Map));

	return self;
}
void Game_Map_destroy(Game_Map *self) {
	free((void*)self->grid);
	free(self);
}
