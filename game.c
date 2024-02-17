
#include "game.h"

typedef struct {
	char *array;
	unsigned char width;
	unsigned char height;
} _Map;

_Map _Map_initialize(char *stringFilepath);
void _Map_destroy(_Map *self);
void _Map_draw(_Map *self);

void temp_Map_print(_Map *self) {
	for (int y = 0; y < self->height; ++y) {
		for (int x = 0; x < self->width; ++x) {
			printf(" %c", self->array[y*self->height + x]);
		}
		printf("\n");
	}
}

#define GAME_TILE_EMPTY '.'
#define GAME_TILE_WALL 'H'
#define GAME_TILE_SLIME '@'
#define GAME_TILE_LIME '$'
#define GAME_TILE_WATER 'w'
#define GAME_TILE_BOX '#'
#define GAME_TILE_UNSTABLEGROUND '0'
//lava (l), ice (i), cracked ice (h), peppers (~), fire (!)


unsigned char Game_main(int temp_level) {

	_Map map = _Map_initialize("assets/levels/1.txt");

	const unsigned char keybsLength = 4;
	char keyLabels[4] = {'w', 'q', 's', 'a'};

	Keybutton *keybs = Input_initializeKeybuttons(keyLabels, keybsLength); 

	unsigned char nextControl = 0;
	
	while (1) {
	if (Input_checkQuit()) {
			nextControl = 0;
			break;
		}

		switch (Input_checkKeybuttons(keybs, keybsLength)) {
			case 0:
				break;
			case 1:
				printf("^\n");
				break;
			case 2:
				printf(">\n");
				break;
			case 3:
				printf("v\n");
				break;
			case 4:
				printf("<\n");
				break;
			default:
				perror("| Error! Unrecognized keyLabel from Input_checkKeybuttons |");
				exit(0);
		};

		_Map_draw(&map);

	}

	_Map_destroy(&map);
	Input_destroyKeybuttons(keybs);
	return nextControl;
}


_Map _Map_initialize(char *stringFilepath) {
	
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
			case GAME_TILE_EMPTY:
				*pos = GAME_TILE_EMPTY;
				pos++;
				break;
			case GAME_TILE_WALL:
				*pos = GAME_TILE_WALL;
				pos++;
				break;
			case GAME_TILE_SLIME:
				*pos = GAME_TILE_SLIME;
				pos++;
				break;
			case GAME_TILE_LIME:
				*pos = GAME_TILE_LIME;
				pos++;
				break;
			case GAME_TILE_WATER:
				*pos = GAME_TILE_WATER;
				pos++;
				break;
			case GAME_TILE_BOX:
				*pos = GAME_TILE_BOX;
				pos++;
				break;
			case GAME_TILE_UNSTABLEGROUND:
				*pos = GAME_TILE_UNSTABLEGROUND;
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

	_Map self = {
		.array = map,
		.width = width,
		.height = height
	};
	temp_Map_print(&self);
	return self;
}
void _Map_destroy(_Map *self) {
	free(self->array);
	self->array = NULL;
}

#define SIZE 25
void _Map_draw(_Map *self) {
	void *texture = NULL;
	for (unsigned char y = 0; y < self->height; ++y) {
		for (unsigned char x = 0; x < self->width; ++x) {

			switch (self->array[y*self->height + x]) {
				case GAME_TILE_EMPTY:
					break;
				case GAME_TILE_WATER:
					texture = Rendering_createTexture("assets/textures/water.bmp");
					Rendering_printTexture(texture, x*SIZE, y*SIZE, SIZE, SIZE);
					Rendering_destroyTexture(texture);
					break;
				case GAME_TILE_WALL:
					texture = Rendering_createTexture("assets/textures/wall.bmp");
					Rendering_printTexture(texture, x*SIZE, y*SIZE, SIZE, SIZE);
					Rendering_destroyTexture(texture);
					break;
				case GAME_TILE_LIME:
					texture = Rendering_createTexture("assets/textures/lime.bmp");
					Rendering_printTexture(texture, x*SIZE, y*SIZE, SIZE, SIZE);
					Rendering_destroyTexture(texture);
					break;
				case GAME_TILE_SLIME:
					texture = Rendering_createTexture("assets/textures/slime.bmp");
					Rendering_printTexture(texture, x*SIZE, y*SIZE, SIZE, SIZE);
					Rendering_destroyTexture(texture);
					break;
				default:
					perror("| Error! Unrecognized value in game map. |\n");
					exit(0);
			};
		}
	}
	Rendering_present();
}
