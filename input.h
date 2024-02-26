#ifndef INPUT_H
#define INPUT_H

typedef struct Keybutton Keybutton;

void Input_initialize();

void Input_resetKeyboard();

Keybutton *Input_initializeKeybuttons(const char *keybuttonLabels, unsigned char keybuttonsLength);
void Input_destroyKeybuttons(Keybutton *arrKeybuttons);

unsigned char Input_checkKeybuttons(Keybutton *keybuttons, unsigned char keybuttonsLength);

unsigned char Input_checkQuit();
unsigned char Input_checkAnyKeypress();


#endif
