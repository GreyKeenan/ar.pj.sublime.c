
#include "game_map.h"

Game_Map Game_Map_initialize(const char *path, const Game_Object *staticGameObjects, const void **gameEntityTextures) {
	Game_Map self;

	FILE *fp = fopen(path, "r");
	if (!fp) {
		perror("Opening level file failed");
		exit(1);
	}

	int c = 0;

	self.width = 0;
	self.height = 0;
	while ((c = fgetc(fp)) != 'x') {
		self.width = self.width * 10 + (c - '0');
	}
	while ((c = fgetc(fp)) != '\n') {
		self.height = self.height * 10 + (c - '0');
	} //todo: error handling for missing/unformatted size

	self.grid = malloc(sizeof(*self.grid) * (self.width * self.height));
	self.entities = malloc(sizeof(*self.entities) * 10);
	self.players = malloc(sizeof(*self.players) * GAME_MAP_MAX_PLAYERS);

	unsigned char entityCount = 0; //temp
	self.playersCount = 0;

	const Game_Object **pos = self.grid;
	while ( (c = fgetc(fp)) != EOF) {
		//ERROR: Doesnt check if writing past [map] in memory
		switch (c) {
			case ' ': break;
			case '\n': break;
			case '\t': break;
			case GAME_MAP_TILE_EMPTY:
				*pos = NULL;
				pos++;
				break;
			case GAME_MAP_TILE_WATER:
				*pos = &(staticGameObjects[0]);
				pos++;
				break;
			case GAME_MAP_TILE_WALL:
				*pos = &(staticGameObjects[1]);
				pos++;
				break;
			case GAME_MAP_TILE_LIME:
				*pos = &(staticGameObjects[1]);
				pos++;
				break;
			case GAME_MAP_TILE_SLIME:
				self.players[self.playersCount] = Game_Entity_initialize(
					gameEntityTextures[0],
					true,
					NULL,
					0,0 //fix pos
				);

				*pos = (Game_Object*)&(self.players[self.playersCount]); //can just do ptr arithmetic here
				self.playersCount;

				//todo: count players

				pos++;
				break;
			case GAME_MAP_TILE_BOX:
				self.entities[entityCount] = Game_Entity_initialize(
					gameEntityTextures[1],
					true,
					NULL,
					0,0 //fix pos
				);
				*pos = (Game_Object*)&(self.entities[entityCount]);
				entityCount++;
				pos++;
				break;
			case GAME_MAP_TILE_UNSTABLEGROUND:
				self.entities[entityCount] = Game_Entity_initialize(
					gameEntityTextures[2],
					true,
					NULL,
					0,0 //fix pos
				);
				*pos = (Game_Object*)&(self.entities[entityCount]);
				entityCount++;
				pos++;
				break;
			default: 
				perror("Unrecognized key when mapping level");
				exit(EXIT_FAILURE);
				break;
		};
	}


	fclose(fp);

	return self;
}

void Game_Map_destroy(Game_Map *self) {
	free(self->grid);
	self->grid = NULL;
	free(self->entities);
	self->entities = NULL;
	free(self->players);
	self->players = NULL;
}

#define TEMP_SIZE 50
void Game_Map_draw(Game_Map *self) {
	for (unsigned char y = 0; y < self->height; ++y) {
		for (unsigned char x = 0; x < self->width; ++x) {
			const Game_Object* obj = self->grid[y * self->height + x];
			if (obj) {
				Rendering_printTexture(obj->texture, x*TEMP_SIZE, y*TEMP_SIZE, TEMP_SIZE, TEMP_SIZE);
			}
		}
	}
}
