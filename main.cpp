/*
 * main.cpp
 *
 *  Created on: May 20, 2019
 *      Author: eric
 */

#include <SDL/SDL.h>

SDL_Surface* background = NULL;
SDL_Surface* sprite = NULL;
SDL_Surface* backbuffer = NULL;

SDL_Rect spritePos;

bool ProgramIsRunning();
bool LoadImages();
void FreeImages();

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

	if (!LoadImages())
	{
		printf("Images failed to load\n");
		FreeImages();
		SDL_Quit();
		return 1;
	}

	spritePos.x = 0;
	spritePos.y = 250;

	while (ProgramIsRunning())
	{
		spritePos.x += 5;

		if (spritePos.x > 800)
		{
			spritePos.x = -200;
		}

		SDL_BlitSurface(background, NULL, backbuffer, NULL);
		SDL_BlitSurface(sprite, NULL, backbuffer, &spritePos);

		SDL_Delay(20);
		SDL_Flip(backbuffer);
	}

	FreeImages();

	SDL_Quit();

	return 0;
}

bool ProgramIsRunning()
{
	SDL_Event event;
	bool running = true;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			running = false;
		}
	}

	return running;
}

bool LoadImages()
{
	background = SDL_LoadBMP("graphics/background.bmp");

	if (background == NULL)
	{
		return false;
	}

	sprite = SDL_LoadBMP("graphics/spaceship.bmp");

	if (sprite == NULL)
	{
		return false;
	}

	return true;
}

void FreeImages()
{
	if (background != NULL)
	{
		SDL_FreeSurface(background);
		background = NULL;
	}

	if (sprite != NULL)
	{
		SDL_FreeSurface(sprite);
		sprite = NULL;
	}
}
