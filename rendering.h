#ifndef RENDERING_H
#define RENDERING_H


#include <stdio.h>
#include "SDL2/SDL.h"

void Rendering_initialize();
void Rendering_destroy();

void Rendering_present();
void Rendering_clear();

void *Rendering_createTexture(const char *filepath);
void Rendering_destroyTexture(const void *texture);

void Rendering_printTexture(const void *texture, const int x, const int y, const int width, const int height);


#endif
