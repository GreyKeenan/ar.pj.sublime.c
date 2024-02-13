#ifndef INPUT_H
#define INPUT_H


typedef struct {
	unsigned int delayUntil;
	unsigned int scancode;
	unsigned char isPressed;
} Input_Keypress;
typedef struct {
	const unsigned char *keyboardState;
	Input_Keypress *keypresses;
	unsigned char keypressesCount;
} Input_Handler;
//set up here to only allow 1 input per frame, since that makes sense for this kind of game.
	// and yes, technically could just use PollEvent then, but I wanted to set it up 'properly'

Input_Handler Input_Handler_initialize();
void Input_Handler_destroy(Input_Handler *self);

unsigned char Input_Handler_update(Input_Handler *self);
	//returns id corresponding to whatever key was pressed/triggered this frame
	//0 = nothing
	//for now, id correlates to position in array + 1


#endif
