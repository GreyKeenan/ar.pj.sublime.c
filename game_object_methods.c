
#include "game_object_methods.h"

bool Game_Object_onPushDefault(Game_Object *self, void *_, char __, char ___) {
	return !self->collides;
}
void Game_Object_onExitDefault(Game_Object *self) {
}

bool Game_Entity_onPushPushable(Game_Object *uncastself, void *map, char directionX, char directionY) {

	Game_Entity *self = (Game_Entity *)uncastself;

	Game_Object *reciever = Game_Map_index(map, self->x + directionX, self->y + directionY);

	if (reciever == NULL || reciever->onPush(reciever, map, directionX, directionY)) {
		Game_Entity_move(self, map, self->x + directionX, self->y + directionY);
		return true;
	}
	return false;
}
