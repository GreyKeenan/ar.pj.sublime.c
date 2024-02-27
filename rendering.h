#ifndef RENDERING_H
#define RENDERING_H

#include "renderingT.h"

void Rendering_initialize();
void Rendering_destroy();

void Rendering_present();
void Rendering_clear();

RenderingT_texture *Rendering_createTexture(const char *filepath);
void Rendering_destroyTexture(RenderingT_texture *texture);

void Rendering_printTexture(RenderingT_texture *texture, int x, int y, int width, int height);


#endif
