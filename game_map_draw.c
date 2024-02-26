
#include "rendering.h"

#include "game_map_impl.h"
#include "game_map_index.h"

#include "game_tile_impl.h"
//#include "game_entity_forw.h"

#include "game_map_draw.h"

#define TEMP_SIZE 25

void _drawTile(const Game_Tile *tile, unsigned char x, unsigned char y);


void Game_Map_draw(const Game_Map *self) {
	for (unsigned char y = 0; y < self->height; ++y) {
		for (unsigned char x = 0; x < self->width; ++x) {
			_drawTile(Game_Map_getIndex(self, x, y), x, y);
		}
	}
}

void _drawTile(const Game_Tile *tile, unsigned char x, unsigned char y) {
	Rendering_printTexture(tile->texture, x*TEMP_SIZE,y*TEMP_SIZE, TEMP_SIZE,TEMP_SIZE);
}
