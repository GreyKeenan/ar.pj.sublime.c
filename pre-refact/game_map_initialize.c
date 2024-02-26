
#include "game_map_initialize.h"

Game_Map _measure(FILE *fp);
void _cut(Game_Map *self, FILE *fp, const Game_Object *staticGameObjects, const void **gameEntityTextures);


Game_Map Game_Map_initialize(const char* path, const Game_Object *staticGameObjects, const void **gameEntityTextures) {
	
	FILE *fp = fopen(path, "r");
	if (!fp) {
		perror("Opening level file failed");
		exit(1);
	}

	Game_Map self = _measure(fp);

	rewind(fp);
	_cut(&self, fp, staticGameObjects, gameEntityTextures);

	fclose(fp);
	return self;
}


Game_Map _measure(FILE *fp) {

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
					//putting (!firstWidth) check in here would reduce num of checks run each time
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
			case GAME_MAP_TILE_LIME:
				goto entityCase;
			case GAME_MAP_TILE_BOX:
				goto entityCase;
			case GAME_MAP_TILE_UNSTABLEGROUND:
				goto entityCase;
			default:
				width++;
				break;
		};
		continue;
		entityCase:
			entityCount++;
			width++;
			continue;
	}

	if (!playerCount) {
		perror("map error: no player found");
		exit(1);
	}

	Game_Map self = {
		.width = firstWidth,
		.height = height,
		.playerCount = playerCount,
		.entityCount = entityCount,
		.entities = malloc(sizeof(*self.entities) * (playerCount + entityCount)),
		.grid = malloc(sizeof(*self.grid) * (firstWidth * height))
	};

	return self;
}


void _cut(Game_Map *self, FILE *fp, const Game_Object *staticGameObjects, const void **gameEntityTextures) {
	unsigned char playerCount = 0;
	unsigned char entityCount = self->playerCount;

	int c = 0;
	for (unsigned char y = 0; y < self->height; ++y) {
		for (unsigned char x = 0; x < self->width; ++x) {
			c = fgetc(fp);
			while (c == ' ' || c == '\n' || c == '\t') {
				c = fgetc(fp);
			}
			if (c == EOF) {
				perror("Error while populating map. Premature EOF.");
				exit(1);
			}

			switch (c) {
				case GAME_MAP_TILE_EMPTY:
					Game_Map_setIndex(self, x,y, NULL);
					break;
				case GAME_MAP_TILE_WATER:
					Game_Map_setIndex(self, x,y, staticGameObjects + 0);
					break;
				case GAME_MAP_TILE_WALL:
					Game_Map_setIndex(self, x,y, staticGameObjects + 1);
					break;
				case GAME_MAP_TILE_SLIME:
					self->entities[playerCount] = Game_Entity_createSlime(
						gameEntityTextures[0],
						NULL,
						x,y
					);
					goto incrementPlayer;
				case GAME_MAP_TILE_LIME:
					self->entities[entityCount] = Game_Entity_createLime(
						gameEntityTextures[1],
						NULL,
						x,y
					);
					goto incrementEntity;
				case GAME_MAP_TILE_BOX:
					self->entities[entityCount] = Game_Entity_createBox(
						gameEntityTextures[2],
						NULL,
						x,y
					);
					goto incrementEntity;
				/*
				case GAME_MAP_TILE_UNSTABLEGROUND:
					self->entities[entityCount] = Game_Entity_createUnstableGround(
						gameEntityTextures[3],
						NULL,
						x,y
					);
					goto incrementEntity;
				*/
				default: 
					perror("Unrecognized key when mapping level");
					exit(1);
					break;
			};
			continue;

			incrementPlayer:
				Game_Map_setIndex(self, x,y, (const Game_Object *)(self->entities + playerCount));
				playerCount++;
				continue;
			incrementEntity:
				Game_Map_setIndex(self, x,y, (const Game_Object *)(self->entities + entityCount));
				entityCount++;
				continue;
		}
	}
}
