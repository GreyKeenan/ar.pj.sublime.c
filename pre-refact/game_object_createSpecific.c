
#include "game_object_createSpecific.h"

Game_Object Game_Object_createWater(const void* texture) {
	return Game_Object_initialize(
		texture,
		0,
		&Game_Object_onPushDefault,
		&Game_Object_onExitDefault
	);
}
Game_Object Game_Object_createWall(const void* texture) {
	return Game_Object_initialize(
		texture,
		1,
		&Game_Object_onPushDefault,
		&Game_Object_onExitDefault
	);
}

Game_Entity Game_Entity_createSlime(const void* texture, Game_Object *foundation, unsigned char x, unsigned char y) {
	return Game_Entity_initialize(
		texture,
		1,
		&Game_Object_onPushDefault,
		&Game_Object_onExitDefault,
		foundation,
		x,y
	);
}
Game_Entity Game_Entity_createLime(const void* texture, Game_Object *foundation, unsigned char x, unsigned char y) {
	return Game_Entity_initialize(
		texture,
		0,
		&Game_Object_onPushDefault,
		&Game_Object_onExitDefault,
		foundation,
		x,y
	);
}
Game_Entity Game_Entity_createBox(const void* texture, Game_Object *foundation, unsigned char x, unsigned char y) {
	return Game_Entity_initialize(
		texture,
		1,
		&Game_Entity_onPushPushable,
		&Game_Object_onExitDefault,
		foundation,
		x,y
	);
}
