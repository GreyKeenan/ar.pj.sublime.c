
#include "game_map_index.h"

#include <stdlib.h>
#include <stdio.h>

#include "game_map.h"

bool Game_Map_isInBounds(const Game_Map *self, unsigned char x, unsigned char y) {
	return (x < self->width) && (y < self->height); //consider using signed int here so can check negative vals and stuff
}

void *Game_Map_getIndex(const Game_Map *self, unsigned char x, unsigned char y) {
	if (!Game_Map_isInBounds) {
		perror("Map Error: getting index out of bounds.");
		exit(1);
	}
	return self->grid[x + y * self->width];
}
void Game_Map_setIndex(Game_Map *self, unsigned char x, unsigned char y, void *to) {
	if (!Game_Map_isInBounds) {
		perror("Map Error: setting index out of bounds.");
		exit(1);
	}
	self->grid[x + y * self->width] = to;
}
