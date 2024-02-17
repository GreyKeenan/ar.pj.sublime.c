
#include "startMenu.h"

unsigned char StartMenu_main() {
	unsigned char nextControl = 0;

	while (1) {
		if (Input_checkQuit()) {
			nextControl = 0;
			break;
		}
		if (Input_checkAnyKeypress()) {
			nextControl = 2;
			break;
		}
		

	}

	return nextControl;
}
