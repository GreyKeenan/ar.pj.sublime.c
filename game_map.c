
#include "game_map.h"

Game_Map Game_Map_initialize(const char *path, const Game_Object *staticGameObjects, const void **gameEntityTextures) {

	FILE *fp = fopen(path, "r");
	if (!fp) {
		perror("Opening level file failed");
		exit(1);
	}

	unsigned char playerCount = 0;
	unsigned char entityCount = 0;
	unsigned char firstWidth = 0;
	unsigned char width = 0;
	unsigned char height = 0;
	//doesnt check if these ^ exceed limit of 255 / I think would need to count them as ints or shorts to check it

	int c = 0;

	//get: width, height, size, entityCount, playerCount
	while ((c = fgetc(fp)) != EOF) {
		switch (c) {
			case ' ': break;
			case '\t': break;
			case '\n': 
				if (!width) {
					break;
				}
				if (!firstWidth) {
					firstWidth = width;
					width = 0;
					height++;
					break;
				}
				if (width != firstWidth) {
					//putting (!height) check in here would reduce num of checks run each time
					perror("map error: uneven row widths");
					exit(1);
				}
				width = 0;
				height++;
				break;
			case GAME_MAP_TILE_SLIME:
				playerCount++;
				width++;
				break;
			case GAME_MAP_TILE_BOX:
				goto entityCase;
			case GAME_MAP_TILE_UNSTABLEGROUND:
				goto entityCase;
			default:
				width++;
				break;
			entityCase:
				entityCount++;
				width++;
				break;
		};
	}

	if (!playerCount) {
		perror("map error: no player found");
		exit(1);
	}
	Game_Map self = {
		.width = firstWidth,
		.height = height,
		.playerCount = playerCount,
		.entityCount = entityCount
	};
	printf("%d, %d / %d + %d\n", self.width, self.height, self.playerCount, self.entityCount);

	self.entities = malloc(sizeof(*self.entities) * (self.playerCount + self.entityCount));
	self.grid = malloc(sizeof(*self.grid) * (self.width * self.height));

	const Game_Object **pos = self.grid;
	playerCount = 0;
	entityCount = self.playerCount;

	rewind(fp);
	while ((c = fgetc(fp)) != EOF) {
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
				*pos = &(staticGameObjects[2]);
				pos++;
				break;
			case GAME_MAP_TILE_SLIME:
				self.entities[playerCount] = Game_Entity_initialize(
					gameEntityTextures[0],
					true,
					NULL,
					0,0 //fix pos
				);

				*pos = (Game_Object*)(self.entities + playerCount);
				playerCount++;
				pos++;
				break;
			case GAME_MAP_TILE_BOX:
				self.entities[entityCount] = Game_Entity_initialize(
					gameEntityTextures[1],
					true,
					NULL,
					0,0 //fix pos
				);
				*pos = (Game_Object*)(self.entities + entityCount);
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
				*pos = (Game_Object*)(self.entities + entityCount);
				entityCount++;
				pos++;
				break;
			default: 
				perror("Unrecognized key when mapping level");
				exit(1);
				break;
			//todo: specifying foundation of entities
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
}

#define TEMP_SIZE 50
void Game_Map_draw(Game_Map *self) {
	for (unsigned char y = 0; y < self->height; ++y) {
		for (unsigned char x = 0; x < self->width; ++x) {
			const Game_Object* obj = self->grid[y * self->height + x];
			//need to draw lower-layer first if is entity
			if (obj) {
				Rendering_printTexture(obj->texture, x*TEMP_SIZE, y*TEMP_SIZE, TEMP_SIZE, TEMP_SIZE);
			}
		}
	}
}
