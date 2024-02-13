
#include <stdio.h>
#include <stdlib.h>
#include "SDL2/SDL.h"

#include "input.h"
void Input_moveNorth();
void Input_moveEast();
void Input_moveSouth();
void Input_moveWest();
void _walkTriggerQueue(GameInputHandler *self, char index, char previous);

const char EMPTY = -1;

GameInputHandler GameInputHandler_initialize() {
	unsigned char triggerCount = 4;
	Input_TriggerNode *triggers = malloc(sizeof(Input_TriggerNode) * triggerCount);
	
	

	GameInputHandler self = {
		.triggers = triggers
		, .head = 0
		, .tail = triggerCount - 1
		, .keyboardState = SDL_GetKeyboardState(NULL)
	};

	triggers->target = 1;
	triggers->isPressed = 0;
	triggers->scancode = SDL_SCANCODE_W;
	triggers->call = &Input_moveNorth;

	triggers++;
	triggers->target = 2;
	triggers->isPressed = 0;
	triggers->scancode = SDL_SCANCODE_Q;
	triggers->call = &Input_moveEast;

	triggers++;
	triggers->target = 3;
	triggers->isPressed = 0;
	triggers->scancode = SDL_SCANCODE_S;
	triggers->call = &Input_moveSouth;

	triggers++;
	triggers->target = EMPTY;
	triggers->isPressed = 0;
	triggers->scancode = SDL_SCANCODE_A;
	triggers->call = &Input_moveWest;

	return self;
}
void GameInputHandler_destroy(GameInputHandler *self) {
	free(self->triggers);
	self->triggers = NULL;
	self->keyboardState = NULL;
}

void GameInputHandler_check(GameInputHandler *self) {
	_walkTriggerQueue(self, self->head, EMPTY);
}


void _walkTriggerQueue(GameInputHandler *self, char index, char previous) {
	Input_TriggerNode *current = self->triggers + index;
	
	if (self->keyboardState[current->scancode]) {
		current->call();
		//set as new tail
		if (current->target == EMPTY) { //is already the tail
			return;
		}

		if (previous == EMPTY) { //current was the head
			self->head = current->target;	
		} else { //current was not the head
			self->triggers[previous].target = current->target;
		}

		current->target = EMPTY; //set current to be tail
		self->triggers[self->tail].target = index;
		self->tail = index;
		return;
	}
	if (current->target == EMPTY) {
		return;
	}
	_walkTriggerQueue(self, current->target, index);
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
