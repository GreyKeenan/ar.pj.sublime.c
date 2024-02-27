
#include "game_map.h"

#include <stdlib.h>
#include <string.h>

Game_Map *Game_Map_init(unsigned char width, unsigned char height) {
	Game_Map *self = malloc(sizeof(Game_Map));

	Game_Map temp = {
		.grid = malloc(sizeof(void*) * (width * height)),
		.width = width,
		.height = height
	};
	memcpy(self, &temp, sizeof(Game_Map));

	return self;
}

void Game_Map_destroy(Game_Map *self) {
	free(self->grid);
	free(self);
}