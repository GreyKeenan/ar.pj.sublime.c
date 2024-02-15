#ifndef RENDERING_H
#define RENDERING_H

#include "SDL2/SDL.h"

#include "game.h"

typedef struct {
	SDL_Window *window;
	SDL_Renderer *renderer;
} Rendering_Handler;

Rendering_Handler Rendering_initializeSDL();
void Rendering_deinitializeSDL(Rendering_Handler *self);

void Rendering_go(Rendering_Handler *self, Game_Level *level);


#endif
