
#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"

#include "input.h"

const unsigned char KEYPRESSESCOUNT = 4;

void _initialize_keypresses(Input_Handler *self) {
	Input_Keypress *kp = self->keypresses;

	kp->scancode = SDL_SCANCODE_W;
	kp->delayUntil = 0;
	kp->isPressed = 0;

	kp++;
	kp->scancode = SDL_SCANCODE_Q;
	kp->delayUntil = 0;
	kp->isPressed = 0;

	kp++;
	kp->scancode = SDL_SCANCODE_S;
	kp->delayUntil = 0;
	kp->isPressed = 0;

	kp++;
	kp->scancode = SDL_SCANCODE_A;
	kp->delayUntil = 0;
	kp->isPressed = 0;
}
Input_Handler Input_Handler_initialize() {
	
	Input_Keypress *keypresses = malloc(sizeof(Input_Keypress) * KEYPRESSESCOUNT);
	
	Input_Handler self = {
		.keyboardState = SDL_GetKeyboardState(NULL)
		, .keypressesCount = KEYPRESSESCOUNT
		, .keypresses = keypresses
	};

	_initialize_keypresses(&self);

	return self;
}
void Input_Handler_destroy(Input_Handler *self) {
	free(self->keypresses);
	self->keypresses = NULL;
}


unsigned char Input_Handler_update(Input_Handler *self) {
	unsigned char returnCode = 0;
	Input_Keypress *ckp = NULL;
	for (unsigned char i = 0; i < self->keypressesCount; ++i) {
		ckp = self->keypresses + i;
		switch (ckp->isPressed) {
			case 1:
				if (! self->keyboardState[ckp->scancode]) {
					ckp->isPressed = 0;
				}
				break;
			case 0:
				if (self->keyboardState[ckp->scancode]) {
					 ckp->isPressed = 1;
					 returnCode = i + 1;
				}
				break;
		}
	}
	return returnCode;
}
