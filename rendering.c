
#include "rendering.h"

SDL_Window *_window;
SDL_Renderer *_renderer;

void Rendering_initialize() {
	if (SDL_Init(
		SDL_INIT_VIDEO
	) < 0) {
		perror(SDL_GetError());
		exit(0);
	}
	_window = SDL_CreateWindow(
		"Sublime!",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		500,500,
		0
	);
	_renderer = SDL_CreateRenderer(
		_window,
		-1,
		0
	);
}
void Rendering_destroy() {
	SDL_DestroyWindow(_window);
	SDL_DestroyRenderer(_renderer);
	_window = NULL;
	_renderer = NULL;
	SDL_Quit();
}
