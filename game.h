#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h" //a way to not need this here? probably not.

#include "rendering.h"
#include "input.h"

#define GAME_TILE_EMPTY '.'
#define GAME_TILE_WALL 'H'
#define GAME_TILE_SLIME '@'
#define GAME_TILE_LIME '$'
#define GAME_TILE_WATER 'w'
#define GAME_TILE_BOX '#'
#define GAME_TILE_UNSTABLEGROUND '0'
//lava (l), ice (i), cracked ice (h), peppers (~), fire (!)


//todo: if loop is function within Game.c, can keep a lot more of this private

typedef struct {
	const unsigned char *map;
	const unsigned char width;
	const unsigned char height;
} Game_Level;

Game_Level Game_Level_initialize(char *stringFilepath);
void Game_Level_destroy(Game_Level *self);

void Game_mainloop(Rendering_Handler *renderingHandler);


#endif
