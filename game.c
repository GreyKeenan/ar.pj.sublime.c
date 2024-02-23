
#include "game.h"

bool _movePlayer(Game_Map *map, const unsigned char direction);


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
	}; //dont need the ptrs in this array except for in map init

	//ERROR: need to rethink organization of texture* because have to free them at the end

	const void* emptyTexture = Rendering_createTexture("assets/textures/empty.bmp");

	Game_Map map = Game_Map_initialize("assets/levels/1.txt", staticObjects, entityTextures);

	//input stuff
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
				_movePlayer(&map, 0);
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

		Game_Map_draw(&map, emptyTexture);
		Rendering_present();
	}

	Game_Map_destroy(&map);
	Input_destroyKeybuttons(keybs);
	return nextControl;
}


bool _movePlayer(Game_Map *map, const unsigned char direction) {

	//temp: assume is up

	//todo: prioritize proper slime based on order, handle moving multiple slimes properly in general

	unsigned char x = map->entities[0].x;
	unsigned char y = map->entities[0].y;

	Game_Map_moveEntity(map, x, y, x - 1, y - 1);
	
	return true;
}
