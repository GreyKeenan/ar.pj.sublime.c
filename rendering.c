
#include "rendering.h"

Rendering_Handler Rendering_initializeSDL() {
	if (SDL_Init(
		SDL_INIT_VIDEO
	) < 0) {
		printf("\n| Failed to initialize SDL2. Exiting program with error: |\n%s\n", SDL_GetError());
		exit(1);
	}
	Rendering_Handler self = {
		.window = SDL_CreateWindow(
			"Sublime!"
			, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
			, 500, 500
			, 0		
		)
		, .renderer = SDL_CreateRenderer(
			self.window
			, -1
			, 0
		)
	};
	return self;
}
void Rendering_deinitializeSDL(Rendering_Handler *self) {
	SDL_DestroyWindow(self->window);
	SDL_DestroyRenderer(self->renderer);
	self->window = NULL;
	self->renderer = NULL;
	SDL_Quit();
}
