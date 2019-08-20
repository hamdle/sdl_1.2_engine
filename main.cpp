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

SDL_Surface* LoadImage(char* fileName);
bool ProgramIsRunning();
bool LoadFiles();
void FreeFiles();

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

	if (!LoadFiles())
	{
		printf("Images failed to load\n");
		FreeFiles();
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

	FreeFiles();

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

SDL_Surface* LoadImage(char* fileName)
{
	SDL_Surface* imageLoaded = NULL;
	SDL_Surface* processedImage = NULL;

	imageLoaded = SDL_LoadBMP(fileName);

	// Ensure the image was loaded correctly
	if (imageLoaded != NULL)
	{
		processedImage = SDL_DisplayFormat(imageLoaded);

		if (processedImage != NULL)
		{
			Uint32 colorKey = SDL_MapRGB(processedImage->format, 255, 0, 255);
			SDL_SetColorKey(processedImage, SDL_SRCCOLORKEY, colorKey);
		}
	}

	// Return the processed image
	return processedImage;
}

bool LoadFiles()
{
	background = LoadImage("graphics/background.bmp");

	if (background == NULL)
	{
		return false;
	}

	sprite = LoadImage("graphics/spaceship.bmp");

	if (sprite == NULL)
	{
		return false;
	}

	return true;
}

void FreeFiles()
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
