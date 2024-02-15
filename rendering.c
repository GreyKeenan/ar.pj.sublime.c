
#include "rendering.h"

Rendering_Handler Rendering_initializeSDL() {
	if (SDL_Init(
		SDL_INIT_VIDEO
	) < 0) {
		printf("\n| Failed to initialize SDL2. Exiting program with error: |\n%s\n", SDL_GetError());
		exit(1);
	}
	Rendering_Handler self = {
		.window = SDL_CreateWindow(
			"Sublime!"
			, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED
			, 500, 500
			, 0		
		)
		, .renderer = SDL_CreateRenderer(
			self.window
			, -1
			, 0
		)
	};
	return self;
}
void Rendering_deinitializeSDL(Rendering_Handler *self) {
	SDL_DestroyWindow(self->window);
	SDL_DestroyRenderer(self->renderer);
	self->window = NULL;
	self->renderer = NULL;
	SDL_Quit();
}




void _assignImageTexture(SDL_Texture **destinationTexture, SDL_Renderer *renderer, char *stringPath) {
	SDL_Surface *image = SDL_LoadBMP(stringPath);
	*destinationTexture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
}
void _tempDrawMap(SDL_Renderer *renderer, Game_Level *level) {
	SDL_Texture *texture = NULL;

	int y = 0;
	int mx = 0;
	for (int i = 0; i < level->width * level->height; i++) {
		SDL_Rect describeRegion = {(i - mx) *25, y*25, 25, 25};
		if (((i + 1) % level->width) == 0) {
			y++;
			mx += level->width;
		}
		switch (level->map[i]) {
			case GAME_TILE_EMPTY:
				break;
			case GAME_TILE_WATER:
				_assignImageTexture(&texture, renderer, "assets/textures/water.bmp");
				SDL_RenderCopy(renderer, texture, NULL, &describeRegion);
				break;
			case GAME_TILE_WALL:
				_assignImageTexture(&texture, renderer, "assets/textures/wall.bmp");
				SDL_RenderCopy(renderer, texture, NULL, &describeRegion);
				break;
			case GAME_TILE_SLIME:
				_assignImageTexture(&texture, renderer, "assets/textures/slime.bmp");
				SDL_RenderCopy(renderer, texture, NULL, &describeRegion);
				break;
			case GAME_TILE_LIME:
				_assignImageTexture(&texture, renderer, "assets/textures/lime.bmp");
				SDL_RenderCopy(renderer, texture, NULL, &describeRegion);
				break;
			default:
				perror("unrecognized map value");
				exit(1);
		};
		SDL_DestroyTexture(texture);
	}

}

void Rendering_go(Rendering_Handler *self, Game_Level *level) {
	
	_tempDrawMap(self->renderer, level);

	SDL_RenderPresent(self->renderer);

}
