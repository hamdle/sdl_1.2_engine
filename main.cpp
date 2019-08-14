/*
 * main.cpp
 *
 *  Created on: May 20, 2019
 *      Author: eric
 */

#include <SDL/SDL.h>

SDL_Surface* image = NULL;
SDL_Surface* backbuffer = NULL;

int main(int arc, char* args[])
{
	// Init SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		printf("SDL failed to initialize!");
		SDL_Quit();
		return 1;
	}

	backbuffer = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
	SDL_WM_SetCaption("SDL 1.2", NULL);

	// Load the image
	image = SDL_LoadBMP("graphics/image.bmp");

	if (image == NULL)
	{
		printf("Image failed to load\n");
		SDL_Quit();
		return 1;
	}

	// Draw the image
	SDL_BlitSurface(image, NULL, backbuffer, NULL);
	SDL_Flip(backbuffer);

	// Wait
	SDL_Delay(3000);

	SDL_FreeSurface(image);
	SDL_Quit();

	return 0;
}
