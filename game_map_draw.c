
#include "game_map_draw.h"

void _drawTile(const Game_Object *obj, const unsigned char x, const unsigned char y, const void *emptyTexture);


#define TEMP_SIZE 30
//rethink where to store/pass emptyTexture
void _drawTile(const Game_Object *obj, const unsigned char x, const unsigned char y, const void *emptyTexture) {
	if (!obj) {
		Rendering_printTexture(emptyTexture, x*TEMP_SIZE, y*TEMP_SIZE, TEMP_SIZE, TEMP_SIZE);
		return;
	}
	if (!obj->isEntity) {
		Rendering_printTexture(obj->texture, x*TEMP_SIZE, y*TEMP_SIZE, TEMP_SIZE, TEMP_SIZE);
		return;
	}

	_drawTile(((const Game_Entity*)obj)->foundation, x, y, emptyTexture);
	Rendering_printTexture(obj->texture, x*TEMP_SIZE, y*TEMP_SIZE, TEMP_SIZE, TEMP_SIZE);
	return;
}
void Game_Map_draw(const Game_Map *self, const void* emptyTexture) {
	for (unsigned char y = 0; y < self->height; ++y) {
		for (unsigned char x = 0; x < self->width; ++x) {
			_drawTile(Game_Map_index(self, x, y), x, y, emptyTexture);
		}
	}
}
