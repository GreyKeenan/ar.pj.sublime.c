
#include "rendering.h"
#include "startMenu.h"
#include "game.h"

int main(int argc, char **argv) {
	Rendering_initialize();

	StartMenu_run();

	Rendering_destroy();

	printf("\n| ...program endpoint. |\n");
	return 0;
}

