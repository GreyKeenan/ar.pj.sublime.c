
#include "game_level.h"


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

#include "game_map.h"
#include "game_map_index.h"

void _measureMap(FILE *fp, unsigned char *writeTo);

void _populateMap(Game_Map *map, FILE *fp, Game_Map_TileI **tiles);


Game_Level *Game_Level_init(const char *path, Game_Map_TileI **tiles) {
	FILE *fp = fopen(path, "r");
	if (!fp) {
		perror("Opening level file failed");
		exit(1);
	}


	unsigned char mapSpecs[5];
		//width,height, playerCount, limeCount, uniqueTileCount

	_measureMap(fp, mapSpecs);

	Game_Map *map = Game_Map_init(mapSpecs[0], mapSpecs[2]);

	rewind(fp);
	_populateMap(map, fp, tiles);

	
	fclose(fp);

	Game_Level *self = malloc(sizeof(Game_Level));
	
	self->map = map;
	self->playerCount = mapSpecs[2];
	self->limeCount = mapSpecs[3];
	self->uniqueTileCount = mapSpecs[4];

	self->players = malloc(sizeof(*self->players) * self->playerCount);
	self->limes = malloc(sizeof(*self->limes) * self->limeCount);
	self->uniqueTiles = malloc(sizeof(*self->uniqueTiles) * self->uniqueTileCount);

	return self;
}

void Game_Level_destroy(Game_Level *self) {
	Game_Map_destroy(self->map);
	free(self);
}


void _measureMap(FILE *fp, unsigned char *writeTo) {
	
	unsigned char playerCount = 0;
	unsigned char limeCount = 0;
	unsigned char uniqueTileCount = 0;
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
				limeCount++;
				width++;
				break;
			case GAME_MAP_TILE_BOX:
				goto uniqueTileCase;
			case GAME_MAP_TILE_UNSTABLEGROUND:
				goto uniqueTileCase;
			default:
				width++;
				break;
		};
		continue;
		uniqueTileCase:
			uniqueTileCount++;
			width++;
			continue;
	}

	if (!playerCount) {
		perror("map error: no player found");
		exit(1);
	}
	if (!limeCount) {
		perror("map error: no limes found");
		exit(1);
	}

	writeTo[0] = firstWidth;
	writeTo[1] = height;
	writeTo[2] = playerCount;
	writeTo[3] = limeCount;
	writeTo[4] = uniqueTileCount;
}

/*
void _populateMap(Game_Map *map, FILE *fp, Game_Map_TileI **tiles) {
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
					Game_Map_setIndex(self, x,y, tiles[0]);
					break;
				case GAME_MAP_TILE_WATER:
					Game_Map_setIndex(self, x,y, tiles[1]);
					break;
				case GAME_MAP_TILE_WALL:
					Game_Map_setIndex(self, x,y, tiles[2]);
					break;
				case GAME_MAP_TILE_SLIME:
					self->players[playerCount] = (Game_Player *)Game_Entity_createSlime(
						dynamicTileTextures[0],
						NULL,
						x,y
					);
					goto incrementPlayer;
				case GAME_MAP_TILE_LIME:
					self->entities[entityCount] = Game_Entity_createLime(
						dynamicTileTextures[1],
						NULL,
						x,y
					);
					goto incrementEntity;
				case GAME_MAP_TILE_BOX:
					self->entities[entityCount] = Game_Entity_createBox(
						dynamicTileTextures[2],
						NULL,
						x,y
					);
					goto incrementEntity;
				*
				case GAME_MAP_TILE_UNSTABLEGROUND:
					self->entities[entityCount] = (Game_Tile *)Game_Entity_createUnstableGround(
						dynamicTileTextures[3],
						NULL,
						x,y
					);
					goto incrementEntity;
				*
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
*/
