#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include "defs.h"
#include "struct.h"
#include "texture.h"
#include <bits/stdc++.h>
using namespace std;

void loadscoreboard()
{
	SDL_Delay(1000);
	Mix_PlayChannel(-1, Music.gScratch2, 0);
	SDL_Surface *image = SDL_LoadBMP("Images/now.bmp");
	SDL_Texture *texture = SDL_CreateTextureFromSurface(app.gRenderer, image);
	SDL_RenderCopy(app.gRenderer, texture, NULL, NULL);

	/* File pointer to hold reference to our file */
	
	FILE *fPtr;
	long long int a[3], temp;
	char p[10000];
	int i = 0;
	fPtr = fopen("Images/highscore.txt", "r");

	while (fscanf(fPtr, "%lld", &a[i]) == 1)
	{
		i++;
		if (i == 3)
	        break;
	}

	if (score > a[0])
	{
		a[2] = a[1];
		a[1] = a[0];
		a[0] = score;
	}
	else if (score > a[1])
	{
		a[2] = a[1];
		a[1] = score;
	}
	else if (score > a[2])
	{
		a[3] = a[2];
		a[2] = score;
	}

	FILE *fPtw = fopen("Images/highscore.txt", "w");
	fprintf(fPtw, "%lld\n%lld\n%lld\n", a[0], a[1], a[2]);

	fclose(fPtw);
	fclose(fPtr);

	SDL_Color textColor = {255, 255, 255, 255};
		
	SDL_RenderPresent(app.gRenderer);
	SDL_Delay(4000);
	return;
}
