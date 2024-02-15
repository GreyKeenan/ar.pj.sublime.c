#ifndef RENDERING_H
#define RENDERING_H

#include "SDL2/SDL.h"

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
} Rendering_Handler;

Rendering_Handler Rendering_initializeSDL();
void Rendering_deinitializeSDL(Rendering_Handler *self);


#endif
