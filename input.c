
#include <stdlib.h>
#include <stdio.h>
#include "SDL2/SDL.h"

#include "input.h"

const unsigned char *_keyboardState;
SDL_Event _event;

void _verifyKeyId(char id);

typedef struct Keybutton {
	unsigned char isPressed;
	unsigned int scancode;
} Keybutton;

void Input_initialize() {
	_keyboardState = SDL_GetKeyboardState(NULL);
}

void Input_resetKeyboard() {
	SDL_ResetKeyboard();
}

Keybutton *Input_initializeKeybuttons(const char *keybuttonLabels, unsigned char keybuttonsLength) {
	Keybutton *keybuttons = malloc(sizeof(Keybutton) * keybuttonsLength);

	for (unsigned char i = 0; i < keybuttonsLength; ++i) {
		_verifyKeyId(keybuttonLabels[i]);

		keybuttons[i].isPressed = 0;
		keybuttons[i].scancode = SDL_GetScancodeFromKey(keybuttonLabels[i]);
	}
	return keybuttons;
}
void Input_destroyKeybuttons(Keybutton *arrKeybuttons) {
	free(arrKeybuttons);
}

unsigned char Input_checkKeybuttons(Keybutton *keybuttons, unsigned char keybuttonsLength) {
	
	unsigned char returnValue = 0;

	for (unsigned char i = 0; i < keybuttonsLength; ++i) {
		if (_keyboardState[keybuttons[i].scancode] == keybuttons[i].isPressed) {
			continue;
		}
		if (keybuttons[i].isPressed) {
			keybuttons[i].isPressed = 0;
			continue;
		} //rn, if two pressed on same frame it drops one. Should I leave it for next frame?
		returnValue = i + 1;
		keybuttons[i].isPressed = 1;
	}
	return returnValue;
}

unsigned char Input_checkQuit() {
	SDL_PollEvent(&_event);
	return _event.type == SDL_QUIT;
}
unsigned char Input_checkAnyKeypress() {
	return _event.type == SDL_KEYDOWN;
}

void _verifyKeyId(const char id) {
	//should never be 0 since 0 == nothing pressed
	if (97 <= id < 123) { //lowercase letter
		return;
	}
	if (48 <= id < 58) { //is number
		return;
	}
	//todo: think through this better
	perror("\n| Unrecognized input keyId. Exiting program... |\n");
	exit(0);

}
