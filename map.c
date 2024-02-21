
#include "map.h"

void temp_Map_print(const Map *self) {
	for (int y = 0; y < self->height; ++y) {
		for (int x = 0; x < self->width; ++x) {
			printf(" %c", self->array[y*self->height + x]);
		}
		printf("\n");
	}
}

Map Map_initialize(const char *stringFilepath) {
	
	FILE *filepointer = fopen(stringFilepath, "r");
	if (!filepointer) {
		perror("Opening level file failed");
		exit(EXIT_FAILURE);
	}

	int c = 0;

	unsigned char width = 0;
	unsigned char height = 0;
	while ((c = fgetc(filepointer)) != 'x') {
		width = width * 10 + (c - '0');
	}
	while ((c = fgetc(filepointer)) != '\n') {
		height = height * 10 + (c - '0');
	} //todo: error handling for missing/unformatted size

	char *map = malloc(sizeof(char) * (width*height));

	char *pos = map;
	while ( (c = fgetc(filepointer)) != EOF) {
		//ERROR: Doesnt check if writing past [map] in memory
		switch (c) {
			case ' ': break;
			case '\n': break;
			case '\t': break;
			case MAP_TILE_EMPTY:
				*pos = MAP_TILE_EMPTY;
				pos++;
				break;
			case MAP_TILE_WALL:
				*pos = MAP_TILE_WALL;
				pos++;
				break;
			case MAP_TILE_SLIME:
				*pos = MAP_TILE_SLIME;
				pos++;
				break;
			case MAP_TILE_LIME:
				*pos = MAP_TILE_LIME;
				pos++;
				break;
			case MAP_TILE_WATER:
				*pos = MAP_TILE_WATER;
				pos++;
				break;
			case MAP_TILE_BOX:
				*pos = MAP_TILE_BOX;
				pos++;
				break;
			case MAP_TILE_UNSTABLEGROUND:
				*pos = MAP_TILE_UNSTABLEGROUND;
				pos++;
				break;
			default: 
				perror("Unrecognized key when mapping level");
				exit(EXIT_FAILURE);
				break;
		};
	}
	
	if (pos != map + (width*height)) { //make sure map[] is full
		perror("Insufficient map entries for level.");
		exit(1);
	}

	fclose(filepointer);

	Map self = {
		.array = map,
		.width = width,
		.height = height
	};
	temp_Map_print(&self);
	return self;
}
void Map_destroy(Map *self) {
	free(self->array);
	self->array = NULL;
}

#define TEMP_SIZE 25
void Map_draw(const Map *self) {
	void *texture = NULL;
	for (unsigned char y = 0; y < self->height; ++y) {
		for (unsigned char x = 0; x < self->width; ++x) {

			switch (self->array[y*self->height + x]) {
				case MAP_TILE_EMPTY:
					break;
				case MAP_TILE_WATER:
					texture = Rendering_createTexture("assets/textures/water.bmp");
					Rendering_printTexture(texture, x*TEMP_SIZE, y*TEMP_SIZE, TEMP_SIZE, TEMP_SIZE);
					Rendering_destroyTexture(texture);
					break;
				case MAP_TILE_WALL:
					texture = Rendering_createTexture("assets/textures/wall.bmp");
					Rendering_printTexture(texture, x*TEMP_SIZE, y*TEMP_SIZE, TEMP_SIZE, TEMP_SIZE);
					Rendering_destroyTexture(texture);
					break;
				case MAP_TILE_LIME:
					texture = Rendering_createTexture("assets/textures/lime.bmp");
					Rendering_printTexture(texture, x*TEMP_SIZE, y*TEMP_SIZE, TEMP_SIZE, TEMP_SIZE);
					Rendering_destroyTexture(texture);
					break;
				case MAP_TILE_SLIME:
					texture = Rendering_createTexture("assets/textures/slime.bmp");
					Rendering_printTexture(texture, x*TEMP_SIZE, y*TEMP_SIZE, TEMP_SIZE, TEMP_SIZE);
					Rendering_destroyTexture(texture);
					break;
				default:
					perror("| Error! Unrecognized value in game map. |\n");
					exit(0);
			};
		}
	}
}
