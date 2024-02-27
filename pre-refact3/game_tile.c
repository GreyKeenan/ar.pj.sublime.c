
#include "game_tile.h"

#include <stdlib.h>

void Game_Tile_destroy(Game_Map_TileI *self) {
	free(self);
}
