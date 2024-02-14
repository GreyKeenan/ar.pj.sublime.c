#ifndef GAME_H
#define GAME_H


typedef struct {
	const unsigned char *map;
	const unsigned char width;
	const unsigned char height;
} Game_Level;

Game_Level Game_Level_initialize(char *stringFilepath);
void Game_Level_destroy(Game_Level *self);


#endif
