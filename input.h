#ifndef INPUT_H
#define INPUT_H


typedef struct {
	char target; //signed to use -1 for null

	unsigned char isPressed;
	unsigned int scancode;
	void (*call)();
} Input_TriggerNode;

typedef struct {
	/*
	implements queue system within an array to store triggers
	I thought this might be better than storing and checking a 'priority' variable, though perhaps not because you need to go through the entire queue when repeating same key, which prolly happens a lot
		at least, its fine for few, evenly-triggered inputs like this, but not otherwise
	input is a little weird since can only move once per frame, rather than free diagonal movement, and I want it to not be annoying how I prioritize inputs
	*/
	Input_TriggerNode *triggers;
	unsigned char head;
	unsigned char tail;
	const unsigned char *keyboardState;
} GameInputHandler;

GameInputHandler GameInputHandler_initialize();
void GameInputHandler_destroy(GameInputHandler *self);

void GameInputHandler_check(GameInputHandler *self);


#endif
