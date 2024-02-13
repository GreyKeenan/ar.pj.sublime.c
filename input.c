
#include <stdio.h>
#include "SDL2/SDL.h"

#include "input.h"
void Input_moveNorth();
void Input_moveEast();
void Input_moveSouth();
void Input_moveWest();

GameInputHandler GameInputHandler_initialize() {

	GameInputHandler self = {
		.keyboardState = SDL_GetKeyboardState(NULL)
		, .catchNorth = SDL_SCANCODE_W
		, .catchEast = SDL_SCANCODE_Q
		, .catchSouth = SDL_SCANCODE_S
		, .catchWest = SDL_SCANCODE_A
	};
	return self;
}

void GameInputHandler_check(GameInputHandler *self) {

	const unsigned char *keyboardState = self->keyboardState;

	if (keyboardState[self->catchNorth]) { //scancode + 93 == ASCII value, at least for letters
		Input_moveNorth();
	}
	if (keyboardState[self->catchSouth]) {
		Input_moveSouth();
	}
	if (keyboardState[self->catchWest]) {
		Input_moveWest();
	}
	if (keyboardState[self->catchEast]) {
		Input_moveEast();
	}

}

void Input_moveNorth() {
	printf("up\n");
}

void Input_moveSouth() {
	printf("down\n");
}

void Input_moveEast() {
	printf("right\n");
}

void Input_moveWest() {
	printf("left\n");
}
