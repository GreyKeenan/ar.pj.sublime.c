
#include "game_map.h"


void Game_Map_destroy(Game_Map *self) {
	free(self->grid);
	self->grid = NULL;
	free(self->entities);
	self->entities = NULL;
}

/*
void Game_Map_moveEntity(Game_Map *self, const unsigned char fromX, const unsigned char fromY, const unsigned char toX, const unsigned char toY) {
	Game_Entity *entityA = (Game_Entity *)Game_Map_index(self, fromX, fromY);
	if (!entityA->gameObject.isEntity) {
		perror("Attempting to move non-entity in Game_Map_moveEntity() ");
		exit(1);
	}
	Game_Map_setIndex(self, fromX, fromY, entityA->foundation);
	entityA->foundation = Game_Map_index(self, toX, toY);
	Game_Map_setIndex(self, toX, toY, (Game_Object *)entityA);

	entityA->x = toX;
	entityA->y = toY;
}
*/
