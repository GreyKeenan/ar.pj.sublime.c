
#include "game.h"

unsigned char Game_main() {
	
	const Game_Object staticObjects[] = {
		Game_Object_initialize(Rendering_createTexture("assets/textures/water.bmp"), false),
		Game_Object_initialize(Rendering_createTexture("assets/textures/wall.bmp"), true),
		Game_Object_initialize(Rendering_createTexture("assets/textures/lime.bmp"), false)
	};

	const void* entityTextures[] = {
		Rendering_createTexture("assets/textures/slime.bmp"),
		Rendering_createTexture("assets/textures/box.bmp")
		//todo: other textures
	};

	Game_Map map = Game_Map_initialize("assets/levels/1.txt", staticObjects, entityTextures);

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

		Game_Map_draw(&map);
		Rendering_present();
	}

	Game_Map_destroy(&map);
	Input_destroyKeybuttons(keybs);
	return nextControl;
}
