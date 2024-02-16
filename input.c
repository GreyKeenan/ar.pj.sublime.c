
#include "input.h"

void _verifyKeyId(char id);

Input_KeyboardHandler Input_KeyboardHandler_initialize(char *keyIds, unsigned char keysLength) {
	
	_Key *keys = malloc(sizeof(_Key) * keysLength);
	for (unsigned char i = 0; i < keysLength; ++i) {
		_verifyKeyId(keyIds[i]);

		keys[i].id = keyIds[i];
		keys[i].scancode = SDL_GetScancodeFromKey(keyIds[i]);
		keys[i].isPressed = 0;
	}
	
	Input_KeyboardHandler self = {
		.keys = keys,
		.keysLength = keysLength,
		.keyboardState = SDL_GetKeyboardState(NULL)
	};
	return self;
}
void Input_KeyboardHandler_destroy(Input_KeyboardHandler *self) {
	free(self->keys);
	self->keys = NULL;
	self->keyboardState = NULL;
}

unsigned char Input_KeyboardHandler_checkQuit(Input_KeyboardHandler *self) {
	SDL_PollEvent(&(self->event));
	return self->event.type == SDL_QUIT;
}
unsigned char Input_KeyboardHandler_check(Input_KeyboardHandler *self) {
	
	_Key *keys = self->keys;
	unsigned char returnValue = 0;

	for (unsigned char i = 0; i < self->keysLength; i++) {
		if (self->keyboardState[keys[i].scancode] == keys[i].isPressed) {
			continue;
		}
		if (keys[i].isPressed) {
			keys[i].isPressed = 0;
			continue;
		}
		returnValue = i + 1;
		keys[i].isPressed = 1;
	}
	return returnValue;
}


void _verifyKeyId(char id) {
	//can never be 0 since 0 == nothing pressed
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
