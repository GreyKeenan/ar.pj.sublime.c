
#include <stdlib.h>
#include <stdio.h>
#include "SDL2/SDL.h"

#include "rendering.h"
#include "input.h" //todo: ideally dont need to include input in main at all
#include "game.h"

void run(Rendering_Handler *renderingHandler);


int main() {
	printf("\n| Starting Program ... |\n\n");

	Rendering_Handler renderingHandler = Rendering_initializeSDL();

	Game_mainloop(&renderingHandler);
	
	Rendering_deinitializeSDL(&renderingHandler);

	printf("\n| ... Program Complete. |\n");
	return 0;
}

