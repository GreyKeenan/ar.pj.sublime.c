#ifndef INPUT_H
#define INPUT_H


#include <stdlib.h>
#include <stdio.h>
#include "SDL2/SDL.h"

//this input setup only handles 1 action per frame

typedef struct {
	unsigned char isPressed;
	unsigned int scancode;
} Keybutton;

void Input_initialize();
void Input_resetKeyboard();

Keybutton *Input_initializeKeybuttons(const char *keybuttonLabels, const unsigned char keybuttonsLength);
void Input_destroyKeybuttons(Keybutton *arrKeybuttons);

unsigned char Input_checkKeybuttons(Keybutton *keybuttons, const unsigned char keybuttonsLength);

unsigned char Input_checkQuit();
unsigned char Input_checkAnyKeypress();


//?mouse position input?


#endif
