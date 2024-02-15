
#include <stdlib.h>
#include <stdio.h>
#include "SDL2/SDL.h"

#include "rendering.h"
#include "input.h"
#include "game.h"

void run(Rendering_Handler *renderingHandler);


int main() {
	printf("\n| Starting Program ... |\n\n");

	Rendering_Handler renderingHandler = Rendering_initializeSDL();

	run(&renderingHandler);
	
	Rendering_deinitializeSDL(&renderingHandler);

	printf("\n| ... Program Complete. |\n");
	return 0;
}

void run(Rendering_Handler *renderingHandler) {

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
