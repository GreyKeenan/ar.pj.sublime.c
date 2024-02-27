
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "rendering.h"
#include "input.h"

#include "game_tile_impl.h"
#include "game_tile_createTiles.h"

//#include "game_entity_forw.h"
//#invluce "game_player_forw.h"

#include "game_map_impl.h"
#include "game_map_initPopulated.h"
#include "game_map_draw.h"

#include "game.h"

Game_Map *_createMap(const char *path);

unsigned char Game_main() {

	Game_Map *map = _createMap("assets/levels/debug.txt");


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

		Game_Map_draw(map);
		Rendering_present();
	}

	Game_Map_destroy(map);
	Input_destroyKeybuttons(keybs);
	return nextControl;
}


Game_Map *_createMap(const char *path) {

	const RenderingT_texture *tileTextures[] = {
		Rendering_createTexture("assets/textures/empty.bmp"),
		Rendering_createTexture("assets/textures/water.bmp"),
		Rendering_createTexture("assets/textures/wall.bmp"),
		
		Rendering_createTexture("assets/textures/slime.bmp"),
		Rendering_createTexture("assets/textures/lime.bmp"),
		Rendering_createTexture("assets/textures/box.bmp")
	};
	Game_Tile *gameTiles[] = {
		Game_Tile_createEmpty(tileTextures[0]),
		Game_Tile_createWater(tileTextures[1]),
		Game_Tile_createWall(tileTextures[2]),

		Game_Tile_createSlime(tileTextures[3]),
		Game_Tile_createLime(tileTextures[4]),
		Game_Tile_createBox(tileTextures[5])
	};
	//ERROR: NEED TO FREE THE TEXTURES AT SOME POINT / AND TILES
	
	return Game_Map_initPopulated(path, gameTiles);
}
