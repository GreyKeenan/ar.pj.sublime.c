
#include "game.h"


#include <stdlib.h>
#include <stdio.h>

#include "rendering.h"
#include "input.h"

unsigned char _mainloop();

unsigned char Game_main() {


	unsigned char nextControl = _mainloop();


	return nextControl;
}

unsigned char _mainloop() {

	const char keyLabels[] = {'w', 'q', 's', 'a'}; //dont need this later either / also could pass string, but takes an extra char ofc 
	const unsigned char keybsLength = 4;

	Keybutton *keybs = Input_initializeKeybuttons(keyLabels, keybsLength); 


	unsigned char nextControl = 0;
	while (1) {
		if (Input_checkQuit()) {
			nextControl = 0;
			break;
		}

		switch (Input_checkKeybuttons(keybs, keybsLength)) {
			case 0:
				break;
			case 1:
				printf("^\n");
				break;
			case 2:
				printf(">\n");
				break;
			case 3:
				printf("v\n");
				break;
			case 4:
				printf("<\n");
				break;
			default:
				perror("| Error! Unrecognized keyLabel from Input_checkKeybuttons |");
				exit(0);
		};

		Rendering_present();
	}
	Input_destroyKeybuttons(keybs);
	return nextControl;
}
