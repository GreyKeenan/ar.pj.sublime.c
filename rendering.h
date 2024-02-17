#ifndef RENDERING_H
#define RENDERING_H


#include <stdio.h>
#include "SDL2/SDL.h"

void Rendering_initialize();
void Rendering_destroy();

void Rendering_present();

void *Rendering_createTexture(char *filepath);
void Rendering_destroyTexture(void *texture);

void Rendering_printTexture(void *texture, int x, int y, int width, int height);


#endif
