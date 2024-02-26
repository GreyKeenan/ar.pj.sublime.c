
#include "game_object_movement.h"


void Game_Entity_move(Game_Entity *self, Game_Map *map, unsigned char toX, unsigned char toY) {

	Game_Map_setIndex(map, self->x,self->y, self->foundation);
	self->foundation = Game_Map_index(map, toX, toY);
	Game_Map_setIndex(map, toX, toY, (Game_Object *)self);

	self->x = toX;
	self->y = toY;
}
