
#include "game_map.h"

void _drawTile(const Game_Object *obj, const unsigned char x, const unsigned char y, const void *emptyTexture);


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

	const Game_Object **pos = (const Game_Object **)self.grid; //is this the right way to handle the consts?
	playerCount = 0;
	entityCount = self.playerCount;

	firstWidth = 0; //reusing for position vars below
	width = 0;
	height = 0; 

	rewind(fp);
	while ((c = fgetc(fp)) != EOF) {

		width = firstWidth % 8; //tidy this
		height = firstWidth / 8;
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
			case GAME_MAP_TILE_LIME:
				*pos = &(staticGameObjects[2]);
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
			case GAME_MAP_TILE_BOX:
				self.entities[entityCount] = Game_Entity_initialize(
					gameEntityTextures[1],
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
					gameEntityTextures[2],
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

void Game_Map_destroy(Game_Map *self) {
	free(self->grid);
	self->grid = NULL;
	free(self->entities);
	self->entities = NULL;
}


#define TEMP_SIZE 50
//rethink where to store/pass emptyTexture
void _drawTile(const Game_Object *obj, const unsigned char x, const unsigned char y, const void *emptyTexture) {
	if (!obj) {
		Rendering_printTexture(emptyTexture, x*TEMP_SIZE, y*TEMP_SIZE, TEMP_SIZE, TEMP_SIZE);
		return;
	}
	if (!obj->isEntity) {
		Rendering_printTexture(obj->texture, x*TEMP_SIZE, y*TEMP_SIZE, TEMP_SIZE, TEMP_SIZE);
		return;
	}

	_drawTile(((const Game_Entity*)obj)->foundation, x, y, emptyTexture);
	Rendering_printTexture(obj->texture, x*TEMP_SIZE, y*TEMP_SIZE, TEMP_SIZE, TEMP_SIZE);
	return;
}
void Game_Map_draw(const Game_Map *self, const void* emptyTexture) {
	for (unsigned char y = 0; y < self->height; ++y) {
		for (unsigned char x = 0; x < self->width; ++x) {
			const Game_Object* obj = self->grid[y * self->height + x];
			_drawTile(obj, x, y, emptyTexture);
		}
	}
}


Game_Object *Game_Map_index(const Game_Map *self, const unsigned char x, const unsigned char y) {
	return self->grid[y * self->height + x];
}
void Game_Map_setIndex(Game_Map *self, const unsigned char x, const unsigned char y, Game_Object *to) {
	self->grid[y * self->height + x] = to;
}

bool Game_Map_isInBounds(const Game_Map *self, const unsigned char x, const unsigned char y) {
	return (x < self->width) && (y < self->height); //dont have to check negatives cuz unsigned / is it better to accept a signed int so can check?
}

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
