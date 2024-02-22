
#include "game_object.h"


Game_Object Game_Object_initialize(const void* texture, const bool collides) {
	Game_Object self = {
		.texture = texture,
		.collides = collides,
		.isEntity = false
	};
	return self;
}

Game_Entity Game_Entity_initialize(const void* texture, const bool collides, Game_Object *foundation, const unsigned char x, const unsigned char y) {
	Game_Entity self = {
		.gameObject = Game_Object_initialize(texture, collides),
		.foundation = foundation,
		.x = x,
		.y = y
	};
	self.gameObject.isEntity = true;
	return self;
}
