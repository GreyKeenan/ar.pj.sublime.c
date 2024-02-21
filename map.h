#ifndef MAP_H
#define MAP_H

#define MAP_TILE_EMPTY '.'
#define MAP_TILE_WALL 'H'
#define MAP_TILE_SLIME '@'
#define MAP_TILE_LIME '$'
#define MAP_TILE_WATER 'w'
#define MAP_TILE_BOX '#'
#define MAP_TILE_UNSTABLEGROUND '0'
//lava (l), ice (i), cracked ice (h), peppers (~), fire (!)

#include <stdio.h>

#include "rendering.h"

typedef struct {
	char *array;
	const unsigned char width;
	const unsigned char height;
} Map;

void temp_Map_print(const Map *self);

Map Map_initialize(const char *stringFilepath);
void Map_destroy(Map *self);
void Map_draw(const Map *self);


#endif
