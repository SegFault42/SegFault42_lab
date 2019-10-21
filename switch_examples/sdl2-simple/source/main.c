#include <stdlib.h>
#include <stdio.h>
#include <switch.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

int main(void)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
		SDL_Log("SDL_Init: %s\n", SDL_GetError());
		return -1;
	}
	IMG_Init(IMG_INIT_JPG);

	SDL_Window	*win = SDL_CreateWindow("", 0, 0, 1280, 720, 0);
	if (win == NULL) {
		SDL_Log("SDL_CreateWindow: %s\n", SDL_GetError());
		IMG_Quit();
		SDL_Quit();
		return (-1);
	}

	SDL_Renderer	*rend = SDL_CreateRenderer(win, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (rend == NULL) {
		SDL_Log("SDL_CreateRenderer: %s\n", SDL_GetError());
		IMG_Quit();
		SDL_Quit();
		return (-1);
	}

	SDL_Surface * image = IMG_Load("/image.ppm");
	if (image == NULL) {
		IMG_Quit();
		SDL_Quit();
		return (-1);
	}

	SDL_Texture * texture = SDL_CreateTextureFromSurface(rend, image);

	SDL_RenderCopy(rend, texture, NULL, NULL);
	SDL_RenderPresent(rend);

	while (1) {}

	IMG_Quit();
	SDL_Quit();

	return 0;
}
