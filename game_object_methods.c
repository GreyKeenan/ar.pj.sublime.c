
#include "game_object_methods.h"

bool Game_Object_onPushDefault(Game_Object *self, char _, char __) {
	return !self->collides;
}
void Game_Object_onExitDefault(Game_Object *self) {
}
