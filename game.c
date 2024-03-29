
#include "game.h"

bool _movePlayer(Game_Map *map, const char byX, const char byY);


unsigned char Game_main() {
	
	const Game_Object staticObjects[] = {
		Game_Object_createWater(Rendering_createTexture("assets/textures/water.bmp")),
		Game_Object_createWall(Rendering_createTexture("assets/textures/wall.bmp"))
	};

	const void* entityTextures[] = {
		Rendering_createTexture("assets/textures/slime.bmp"),
		Rendering_createTexture("assets/textures/lime.bmp"),
		Rendering_createTexture("assets/textures/box.bmp")
		//todo: other textures
	};

	//ERROR: need to rethink organization of texture* because have to free them at the end

	const void* emptyTexture = Rendering_createTexture("assets/textures/empty.bmp");

	Game_Map map = Game_Map_initialize("assets/levels/debug.txt", staticObjects, entityTextures);

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
				_movePlayer(&map, 0,-1);
				break;
			case 2:
				printf(">\n");
				_movePlayer(&map, 1,0);
				break;
			case 3:
				printf("v\n");
				_movePlayer(&map, 0,1);
				break;
			case 4:
				printf("<\n");
				_movePlayer(&map, -1,0);
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


bool _movePlayer(Game_Map *map, const char byX, const char byY) {

	//todo: prioritize proper slime based on order, handle moving multiple slimes properly in general

	for (unsigned char i = 0; i < map->playerCount; ++i) {
		unsigned char toX = map->entities[i].x + byX;
		unsigned char toY = map->entities[i].y + byY;

		Game_Object *reciever = Game_Map_index(map, toX,toY);
		if (reciever == NULL || reciever->onPush(reciever, map, byX, byY)) {
			Game_Entity_move(
				map->entities + i,
				map,
				toX, toY
			);

		}
	}
	
	return true;
}
