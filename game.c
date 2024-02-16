
#include "game.h"


Game_Level Game_Level_initialize(char* stringFilepath) {

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

	//temp print map
	for (int i = 0; i < width*height; i++) {
		printf("%c ", map[i]);
		if (((i + 1) % 8) == 0) {
			printf("\n");
		}
	}

	Game_Level self = {
		.map = map
		, .width = width
		, .height = height
	};
	return self;
}

void Game_Level_destroy(Game_Level *self) {
	free((void*)self->map);
	self->map = NULL;
}


void Game_mainloop(Rendering_Handler *renderingHandler) {
	SDL_Event event;

	Input_Handler input = Input_Handler_initialize();
	unsigned char keyCode = 0;
	Game_Level level = Game_Level_initialize("assets/levels/1.txt");

	while (1) {
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT) {
			break;
		}
		keyCode = Input_Handler_update(&input);

		switch (keyCode) {
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
		}
		
		Rendering_go(renderingHandler, &level);

	}

	Input_Handler_destroy(&input);
	Game_Level_destroy(&level);
}
