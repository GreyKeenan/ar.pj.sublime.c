
#include <stdlib.h>
#include <stdio.h>
#include "SDL2/SDL.h"

#include "input.h"

void initializeSDL(SDL_Window **_, SDL_Renderer **__);
void run(SDL_Renderer *_);


int main() {
	printf("\n| Starting Program ... |\n\n");

	SDL_Window *window;
	SDL_Renderer *renderer;

	initializeSDL(&window, &renderer);

	run(renderer);
	
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	printf("\n| ... Program Complete. |\n");
	return 0;
}


void initializeSDL(SDL_Window **windowDestination, SDL_Renderer **rendererDestination) {
	if (SDL_Init(
		SDL_INIT_VIDEO
	) < 0) {
		printf("\n| Failed to initialize SDL2. Exiting program with error: |\n%s\n", SDL_GetError());
		exit(1);
	}
	*windowDestination = SDL_CreateWindow(
		"Sublime!"
		, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
		, 500, 500
		, 0		
	);
	*rendererDestination = SDL_CreateRenderer(
		*windowDestination
		, -1
		, 0
	);
	return;
}

void run(SDL_Renderer *renderer) {

	SDL_Event event;

	Input_Handler input = Input_Handler_initialize();
	unsigned char keyCode = 0;

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
	}

	Input_Handler_destroy(&input);
}
