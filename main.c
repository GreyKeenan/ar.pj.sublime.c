
#include "rendering.h"
#include "startMenu.h"
#include "game.h"

int main(int argc, char **argv) {
	Rendering_initialize();

	StartMenu_initialize();
	StartMenu_run();
	StartMenu_destroy();

	Rendering_destroy();
	return 0;
}

