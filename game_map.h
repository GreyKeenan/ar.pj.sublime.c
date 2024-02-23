#ifndef GAME_MAP_H
#define GAME_MAP_H

#define GAME_MAP_TILE_EMPTY '.'
#define GAME_MAP_TILE_WATER 'w'
#define GAME_MAP_TILE_WALL 'H'
#define GAME_MAP_TILE_LIME '$'
#define GAME_MAP_TILE_SLIME '@'
#define GAME_MAP_TILE_BOX '#'
#define GAME_MAP_TILE_UNSTABLEGROUND '0'
//lava (l), ice (i), cracked ice (h), peppers (~), fire (!)

#include <stdlib.h>
#include <stdio.h>

#include "rendering.h"

#include "game_object.h"

typedef struct {
	Game_Object **grid;
	Game_Entity *entities;
	const unsigned char width;
	const unsigned char height;
	const unsigned char playerCount;
	const unsigned char entityCount;
} Game_Map;

Game_Map Game_Map_initialize(const char *path, const Game_Object *staticGameObjects, const void **gameEntityTextures);
void Game_Map_destroy(Game_Map *self);

void Game_Map_draw(const Game_Map *self, const void* emptyTexture);


Game_Object *Game_Map_index(const Game_Map *self, const unsigned char x, const unsigned char y);
void Game_Map_setIndex(Game_Map *self, const unsigned char x, const unsigned char y, Game_Object *to);

bool Game_Map_isInBounds(const Game_Map *self, const unsigned char x, const unsigned char y);

void Game_Map_moveEntity(Game_Map *self, const unsigned char fromX, const unsigned char fromY, const unsigned char toX, const unsigned char toY);
	//doesnt check isInBounds
	//todo: make toY relative to fromY


#endif
