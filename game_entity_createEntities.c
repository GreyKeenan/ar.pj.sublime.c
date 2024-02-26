
#include <stddef.h>

#include "game_entity_impl.h"

#include "game_entity_createEntities.h"

Game_Entity *Game_Entity_createSlime(RenderingT_texture *texture, Game_Tile *foundation, unsigned char x, unsigned char y) {
	return Game_Entity_init(
		texture,
		NULL,
		NULL,
		foundation,
		x,y
	);
}
Game_Entity *Game_Entity_createLime(RenderingT_texture *texture, Game_Tile *foundation, unsigned char x, unsigned char y) {
	return Game_Entity_init(
		texture,
		NULL,
		NULL,
		foundation,
		x,y
	);
}
Game_Entity *Game_Entity_createBox(RenderingT_texture *texture, Game_Tile *foundation, unsigned char x, unsigned char y) {
	return Game_Entity_init(
		texture,
		NULL,
		NULL,
		foundation,
		x,y
	);
}
