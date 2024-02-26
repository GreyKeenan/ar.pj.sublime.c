
#include <stdio.h>
#include "SDL2/SDL.h"

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

void Rendering_present() {
	SDL_RenderPresent(_renderer);
}
void Rendering_clear() {
	SDL_RenderClear(_renderer);
}

RenderingT_texture *Rendering_createTexture(const char *filepath) {
	SDL_Surface *image = SDL_LoadBMP(filepath);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, image);
	SDL_FreeSurface(image);
	return (RenderingT_texture *)texture;
}
void Rendering_destroyTexture(RenderingT_texture *texture) {
	SDL_DestroyTexture((SDL_Texture *)texture);
}

void Rendering_printTexture(RenderingT_texture *texture, int x, int y, int width, int height) {
	SDL_Rect rectangle = {x,y, width,height};
	SDL_RenderCopy(_renderer, (SDL_Texture *)texture, NULL, &rectangle);
}
