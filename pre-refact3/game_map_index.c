
#include "game_map_index.h"


#include <stdlib.h>
#include <stdio.h>

#include "game_map.h"

bool Game_Map_isInBounds(const Game_Map *self, unsigned char x, unsigned char y) {
	return (x < self->width) && (y < self->height);
	//not checking negatives because unsigned / consider using int16 or int32
}

Game_Map_TileI *Game_Map_getIndex(const Game_Map *self, unsigned char x, unsigned char y) {
	if (!Game_Map_isInBounds(self, x, y)) {
		perror("Map getting index out-of-bounds. Terminating Program");
		exit(1);
	}
	return self->grid[y * self->width + x];
}
void Game_Map_setIndex(Game_Map *self, unsigned char x, unsigned char y, Game_Map_TileI *to) {
	if (!Game_Map_isInBounds(self, x, y)) {
		perror("Map setting index out-of-bounds. Terminating Program");
		exit(1);
	}
	self->grid[y * self->width + x] = to;
}
