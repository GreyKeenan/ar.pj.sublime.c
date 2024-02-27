
#include <stddef.h>

#include "game_tile_impl.h"
#include "game_tile_methods.h"

#include "game_tile_createTiles.h"

Game_Tile *Game_Tile_createEmpty(RenderingT_texture *texture) {
	return Game_Tile_init(
		texture,
		NULL,
		&Game_Tile_method_onPushDefault,
		&Game_Tile_method_onExitDefault
	);
}
Game_Tile *Game_Tile_createWater(RenderingT_texture *texture) {
	return Game_Tile_init(
		texture,
		NULL,
		&Game_Tile_method_onPushDefault,
		&Game_Tile_method_onExitDefault
	);
}
Game_Tile *Game_Tile_createWall(RenderingT_texture *texture) {
	return Game_Tile_init(
		texture,
		NULL,
		&Game_Tile_method_onPushDefault,
		&Game_Tile_method_onExitDefault
	);
}

Game_Tile *Game_Tile_createSlime(RenderingT_texture *texture, Game_Tile *foundation) {
	return Game_Tile_init(
		texture,
		foundation,
		&Game_Tile_method_onPushDefault,
		&Game_Tile_method_onExitDefault
	);
}
Game_Tile *Game_Tile_createLime(RenderingT_texture *texture, Game_Tile *foundation) {
	return Game_Tile_init(
		texture,
		foundation,
		&Game_Tile_method_onPushDefault,
		&Game_Tile_method_onExitDefault
	);
}
Game_Tile *Game_Tile_createBox(RenderingT_texture *texture, Game_Tile *foundation) {
	return Game_Tile_init(
		texture,
		foundation,
		&Game_Tile_method_onPushDefault,
		&Game_Tile_method_onExitDefault
	);
}