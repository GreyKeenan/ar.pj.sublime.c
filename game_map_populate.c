
#include "game_map_populate.h"

Game_Map Game_Map_initializePopulated(const char* path, const Game_Object *staticGameObjects, const void **gameEntityTextures) {

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
	//todo: check for limes?
	Game_Map self = {
		.width = firstWidth,
		.height = height,
		.playerCount = playerCount,
		.entityCount = entityCount
	};
	//printf("%d, %d / %d + %d\n", self.width, self.height, self.playerCount, self.entityCount);

	self.entities = malloc(sizeof(*self.entities) * (self.playerCount + self.entityCount));
	self.grid = malloc(sizeof(*self.grid) * (self.width * self.height));

	const Game_Object **pos = (const Game_Object **)self.grid; //is this the right way to handle the consts?
	playerCount = 0;
	entityCount = self.playerCount;

	firstWidth = 0; //reusing for position vars below
	width = 0;
	height = 0; 

	rewind(fp);
	while ((c = fgetc(fp)) != EOF) {

		width = firstWidth % self.width; //tidy this
		height = firstWidth / self.width;
		//printf("'%c': %d, %d\n", c, width, height);

		switch (c) {
			case ' ': continue;
			case '\n': continue;
			case '\t': continue;


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
			case GAME_MAP_TILE_SLIME:
				self.entities[playerCount] = Game_Entity_initialize(
					gameEntityTextures[0],
					true,
					NULL,
					width,height
				);

				*pos = (Game_Object*)(self.entities + playerCount);
				playerCount++;
				pos++;
				break;
			case GAME_MAP_TILE_LIME:
				self.entities[entityCount] = Game_Entity_initialize(
					gameEntityTextures[1],
					false,
					NULL,
					width,height
				);
				*pos = (Game_Object*)(self.entities + entityCount);
				entityCount++;
				pos++;
				break;
			case GAME_MAP_TILE_BOX:
				self.entities[entityCount] = Game_Entity_initialize(
					gameEntityTextures[2],
					true,
					NULL,
					width,height
				);
				*pos = (Game_Object*)(self.entities + entityCount);
				entityCount++;
				pos++;
				break;
			case GAME_MAP_TILE_UNSTABLEGROUND:
				self.entities[entityCount] = Game_Entity_initialize(
					gameEntityTextures[3],
					true,
					NULL,
					width,height
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

		firstWidth++; //tidy this
	}

	fclose(fp);

	return self;
}
