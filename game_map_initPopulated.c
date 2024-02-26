
#include <stdlib.h>
#include <stdio.h>

#include "game_map_impl.h"
#include "game_map_index.h"

#include "game_tile_createTiles.h"

#include "game_entity_forw.h"
#include "game_entity_createEntities.h"

#include "game_map_initPopulated.h"

#define GAME_MAP_TILE_EMPTY '.'
#define GAME_MAP_TILE_WATER 'w'
#define GAME_MAP_TILE_WALL 'H'
#define GAME_MAP_TILE_LIME '$'
#define GAME_MAP_TILE_SLIME '@'
#define GAME_MAP_TILE_BOX '#'
#define GAME_MAP_TILE_UNSTABLEGROUND '0'
//lava (l), ice (i), cracked ice (h), peppers (~), fire (!)

Game_Map *_measure(FILE *fp);
void _cut(Game_Map *self, FILE *fp, Game_Tile **gameTiles, const RenderingT_texture **entityTextures);

Game_Map *Game_Map_initPopulated(const char* path, Game_Tile **gameTiles, const RenderingT_texture **entityTextures) {

	FILE *fp = fopen(path, "r");
	if (!fp) {
		perror("Opening level file failed");
		exit(1);
	}

	Game_Map *self = _measure(fp);

	rewind(fp);
	_cut(self, fp, gameTiles, entityTextures);

	fclose(fp);
	return self;

}


Game_Map *_measure(FILE *fp) {
	
	unsigned char playerCount = 0;
	unsigned char entityCount = 0;
	unsigned char firstWidth = 0;
	unsigned char width = 0;
	unsigned char height = 0;
	//doesnt check if these ^ exceed limit of 255

	int c = 0;
	while ((c = fgetc(fp)) != EOF) {
		switch (c) {
			case ' ': break;
			case '\t': break;
			case '\n': 
				if (!width) {
					break;
				}
				if (!firstWidth) {
					firstWidth = width;
					width = 0;
					height++;
					break;
				}
				if (width != firstWidth) {
					//putting (!firstWidth) check in here would reduce num of checks run each time
					perror("map error: uneven row widths");
					exit(1);
				}
				width = 0;
				height++;
				break;
			case GAME_MAP_TILE_SLIME:
				playerCount++;
				width++;
				break;
			case GAME_MAP_TILE_LIME:
				goto entityCase;
			case GAME_MAP_TILE_BOX:
				goto entityCase;
			case GAME_MAP_TILE_UNSTABLEGROUND:
				goto entityCase;
			default:
				width++;
				break;
		};
		continue;
		entityCase:
			entityCount++;
			width++;
			continue;
	}

	if (!playerCount) {
		perror("map error: no player found");
		exit(1);
	}

	return Game_Map_init(firstWidth, height, playerCount, entityCount);
	

}
void _cut(Game_Map *self, FILE *fp, Game_Tile **gameTiles, const RenderingT_texture **entityTextures) {
	unsigned char playerCount = 0;
	unsigned char entityCount = 0;

	int c = 0;
	for (unsigned char y = 0; y < self->height; ++y) {
		for (unsigned char x = 0; x < self->width; ++x) {
			c = fgetc(fp);
			while (c == ' ' || c == '\n' || c == '\t') {
				c = fgetc(fp);
			}
			if (c == EOF) { //this isnt really necessary since checks happen at _measure
				perror("Error while populating map. Premature EOF.");
				exit(1);
			}

			switch (c) {
				case GAME_MAP_TILE_EMPTY:
					Game_Map_setIndex(self, x,y, gameTiles[0]);
					break;
				case GAME_MAP_TILE_WATER:
					Game_Map_setIndex(self, x,y, gameTiles[1]);
					break;
				case GAME_MAP_TILE_WALL:
					Game_Map_setIndex(self, x,y, gameTiles[2]);
					break;
				case GAME_MAP_TILE_SLIME:
					self->players[playerCount] = (Game_Player *)Game_Entity_createSlime(
						entityTextures[0],
						NULL,
						x,y
					);
					goto incrementPlayer;
				case GAME_MAP_TILE_LIME:
					self->entities[entityCount] = Game_Entity_createLime(
						entityTextures[1],
						NULL,
						x,y
					);
					goto incrementEntity;
				case GAME_MAP_TILE_BOX:
					self->entities[entityCount] = Game_Entity_createBox(
						entityTextures[2],
						NULL,
						x,y
					);
					goto incrementEntity;
				/*
				case GAME_MAP_TILE_UNSTABLEGROUND:
					self->entities[entityCount] = (Game_Tile *)Game_Entity_createUnstableGround(
						entityTextures[3],
						NULL,
						x,y
					);
					goto incrementEntity;
				*/
				default: 
					perror("Unrecognized key when mapping level");
					exit(1);
					break;
			};
			continue;

			incrementPlayer:
				Game_Map_setIndex(self, x,y, (Game_Tile *)self->players[playerCount]);
				playerCount++;
				continue;
			incrementEntity:
				Game_Map_setIndex(self, x,y, (Game_Tile *)self->entities[entityCount]);
				entityCount++;
				continue;
		}
	}
}
