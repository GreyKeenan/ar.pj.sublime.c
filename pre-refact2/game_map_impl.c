
#include <stdlib.h>
#include <stdio.h>

#include "game_map_impl.h"


Game_Map *Game_Map_init(unsigned char width, unsigned char height, unsigned char playerCount) {
	Game_Map *self = malloc(sizeof(Game_Map));

	self->width = width;
	self->height = height;
	self->playerCount = playerCount;

	self->grid = malloc(sizeof(*self->grid) * (width * height));
	self->players = malloc(sizeof(*self->players) * playerCount);
	//self->dynamicTiles = malloc(sizeof(*self->dynamicTiles) * dynamicTileCount);
	self->dynamicTiles = NULL;

	return self;
}
void Game_Map_destroy(Game_Map *self) {

	for (unsigned char i = 0; i < self->playerCount; ++i) {
		free(self->players[i]);
	}
	free(self->players);

	for (unsigned char i = 0; i < self->dynamicTileCount; ++i) {
		free(self->dynamicTiles[i]);
	}
	free(self->dynamicTiles);

	free(self->grid);

	free(self);
}
