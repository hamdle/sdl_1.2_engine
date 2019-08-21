/*
 * main.cpp
 *
 *  Created on: May 20, 2019
 *      Author: eric
 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

SDL_Surface* background = NULL;
SDL_Surface* sprite = NULL;
SDL_Surface* backbuffer = NULL;

int sprite_frame = 0;
int frame_counter = 0;
int background_x = 0;

const int MaxSpriteFrame = 11;
const int FrameDelay = 2;

SDL_Surface* LoadImage(char* fileName);
void DrawImageFrame(SDL_Surface* image, SDL_Surface* destSurface,
		int x, int y,
		int width, int height, int frame);
bool ProgramIsRunning();
bool LoadFiles();
void FreeFiles();
void DrawImage(SDL_Surface* image, SDL_Surface* destSurface, int x, int y);

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

	while (ProgramIsRunning())
	{
		// Update sprite's frame
		frame_counter++;

		if (frame_counter > FrameDelay)
		{
			frame_counter = 0;
			sprite_frame++;
		}

		if (sprite_frame > MaxSpriteFrame)
		{
			sprite_frame = 0;
		}

		// Update background scrolling
		background_x -= 6;
		if (background_x <= -800)
		{
			background_x = 0;
		}

		// Render the scene
		DrawImage(background, backbuffer, background_x, 0);
		DrawImage(background, backbuffer, background_x + 800, 0);

		DrawImageFrame(sprite, backbuffer,
				350, 250,
				150, 120,
				sprite_frame);

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

	imageLoaded = IMG_Load(fileName);

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

void DrawImageFrame(SDL_Surface* image, SDL_Surface* destSurface,
		int x, int y,
		int width, int height, int frame)
{
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;

	int columns = image->w / width;
	SDL_Rect sourceRect;
	sourceRect.y = (frame / columns) * height;
	sourceRect.x = (frame % columns) * width;
	sourceRect.w = width;
	sourceRect.h = height;

	SDL_BlitSurface(image, &sourceRect, destSurface, &destRect);
}

void DrawImage(SDL_Surface* image, SDL_Surface* destSurface, int x, int y)
{
	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;

	SDL_BlitSurface(image, NULL, destSurface, &destRect);
}

bool LoadFiles()
{
	background = LoadImage("graphics/background.bmp");

	if (background == NULL)
	{
		return false;
	}

	sprite = LoadImage("graphics/demon.bmp");

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
