
#include <stdio.h>

#include "rendering.h"
#include "input.h"

#include "menu.h"
#include "game.h"

void mainloop();


int main(int argc, char **argv) {
	printf("\n| Starting program... |\n\n");

	Rendering_initialize();
	Input_initialize();

	mainloop();

	Rendering_destroy();

	printf("\n| ...program endpoint. |\n");
	return 0;
}

void mainloop() {

	unsigned char nextControl = 1;

	while (nextControl) {

		Input_resetKeyboard();

		switch (nextControl) {
			//0 unreachable
			case 1:
				printf("starting menu\n"); //temp
				nextControl = Menu_main();
				break;
			case 2:
				printf("starting game\n"); //temp
				nextControl = Game_main();
				break;
			default:
				perror("| Unrecognized nextControl in main() loop. Ending peacefully... |\n");
				nextControl = 0;
		};
	}
}

