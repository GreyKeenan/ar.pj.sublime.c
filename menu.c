
#include "rendering.h"
#include "input.h"

#include "menu.h"

unsigned char Menu_main() {
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
