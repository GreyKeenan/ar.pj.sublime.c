#ifndef INPUT_H
#define INPUT_H


#include <stdlib.h>
#include <stdio.h>
#include "SDL2/SDL.h"

//this input setup only handles 1 action per frame

typedef struct {
	char id;
	unsigned char isPressed;
	unsigned int scancode;
} _Key;

typedef struct {
	_Key *keys;
	unsigned char keysLength;
	const unsigned char *keyboardState;
	SDL_Event event;
} Input_KeyboardHandler;

Input_KeyboardHandler Input_KeyboardHandler_initialize(char *keyIds, unsigned char keysLength);
void Input_KeyboardHandler_destroy(Input_KeyboardHandler *self);

unsigned char Input_KeyboardHandler_checkQuit(Input_KeyboardHandler *self);
unsigned char Input_KeyboardHandler_check(Input_KeyboardHandler *self);

//?mouse position input?


#endif
