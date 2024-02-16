
#include "startMenu.h"

void StartMenu_run() {
	char keys[4] = {'w', 'q', 's', 'a'};
	Input_KeyboardHandler inputHandler = Input_KeyboardHandler_initialize(keys, sizeof(keys)/sizeof(char));
	while (1) {
		if (Input_KeyboardHandler_checkQuit(&inputHandler)) {
			break;
		}
		
		switch (Input_KeyboardHandler_check(&inputHandler)) {
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
				perror("| Error! Unrecognized input keyId |");
				exit(0);
		};

	}
	Input_KeyboardHandler_destroy(&inputHandler);
}
