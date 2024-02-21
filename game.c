
#include "game.h"


unsigned char Game_main(int temp_level) {

	Map map = Map_initialize("assets/levels/1.txt");

	const unsigned char keybsLength = 4;
	const char keyLabels[4] = {'w', 'q', 's', 'a'};

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

		Map_draw(&map);
		Rendering_present();

	}

	Map_destroy(&map);
	Input_destroyKeybuttons(keybs);
	return nextControl;
}


