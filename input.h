#ifndef INPUT_H
#define INPUT_H


typedef struct {
	const unsigned char *keyboardState;
	
	unsigned int catchNorth;
	unsigned int catchEast;
	unsigned int catchSouth;
	unsigned int catchWest;

	unsigned int catchNorth_delay;
	unsigned int catchEast_delay;
	unsigned int catchSouth_delay;
	unsigned int catchWest_delay;
} GameInputHandler;

GameInputHandler GameInputHandler_initialize();

void GameInputHandler_check(GameInputHandler *self);


#endif
