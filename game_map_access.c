
#include "game_map_access.h"

bool Game_Map_isInBounds(const Game_Map *self, const unsigned char x, const unsigned char y) {
	return (x < self->width) && (y < self->height); //dont have to check negatives cuz unsigned / is it better to accept a signed int so can check?
}

Game_Object *Game_Map_index(const Game_Map *self, const unsigned char x, const unsigned char y) {
	if (!Game_Map_isInBounds(self, x, y)) {
		perror("Map getting index out-of-bounds. Terminating Program");
		exit(1);
	}
	return self->grid[y * self->width + x];
}
void Game_Map_setIndex(Game_Map *self, const unsigned char x, const unsigned char y, const Game_Object *to) {
	if (!Game_Map_isInBounds(self, x, y)) {
		perror("Map setting index out-of-bounds. Terminating Program");
		exit(1);
	}
	self->grid[y * self->width + x] = (Game_Object *)to;
}
