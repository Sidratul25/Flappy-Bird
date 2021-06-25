#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include "texture.h"
#include "struct.h"
#include <bits/stdc++.h>
using namespace std;


int loadmenu()
{
	bool success = true;
	if (!tex.gMenuTexture.loadFromFile("Images/MENU.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!tex.gMenu1Texture.loadFromFile("Images/1.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!tex.gMenu2Texture.loadFromFile("Images/2.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!tex.gMenu3Texture.loadFromFile("Images/3.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!tex.gMenu4Texture.loadFromFile("Images/4.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	bool menuRun = true;

	while (menuRun)
	{
		tex.gMenuTexture.render(0, 0);
		SDL_Event e;
		int x, y;
		SDL_GetMouseState(&x, &y);
		cout << x << " " << y << endl;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				return 0;
			if (x > 167 && x < 427)
			{
				if(y>249 && y < 275)
				{
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						kol=1;
						Mix_PlayMusic(Music.gMusic,1);
						return 1;
					}
					else
					{
						tex.gMenu1Texture.render(0, 0);
					}
				}
				else if(y>323 && y < 382)
				{
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						return 2;
					}
					else
					{
						tex.gMenu2Texture.render(0, 0);
					}
					
				}
				else if(y> 414 && y < 475)
				{
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						return 3;
					}
					else
					{
						tex.gMenu3Texture.render(0, 0);
					}
					
				}
				else if(y>509 && y < 569)
				{
					if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						return 0;
					}
					else
					{
						tex.gMenu4Texture.render(0, 0);
					}
					
				}
			}

			if (e.type == SDL_KEYDOWN)
			{
				menuRun = false;
			}
		}
		SDL_RenderPresent(app.gRenderer);
	}
	return -1;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load Fonts
	if(!tex.gUBGTexture.loadFromFile("Images/Username.png"))
	{
		printf("Failer to load Username!\n");
		success = false;
	}
	//Open the font
	app.gFont = TTF_OpenFont("Images/Courier.ttf", 34);
	if (app.gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Set text color
		SDL_Color textColor = {176, 48, 96, 255};

		//Load prompt texture
		if (!gPromptTextTexture.loadFromRenderedText("Enter Text: ", textColor))
		{
			printf("Unable to render prompt texture!\n");
			success = false;
		}
	}

	//Load background texture
	if (!tex.gBGTexture.loadFromFile("Images/dreamy day.jpg"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!tex.gPillarTexture.loadFromFile("Images/Pillar1.png"))
	{
		printf("Failed to load pillar texture!\n");
		success = false;
	}
	//Load dot texture
	if (!tex.gDotTexture.loadFromFile("Images/birdy.png"))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}
	if( !tex.gBirdySheetTexture.loadFromFile("Images/birdy2.png" ) )
        {
        printf( "Failed to load walking animation texture!\n" );
        success = false;
        }
       else
       {
        //Set Birdy clips
        rect.gBirdyClips[ 0 ].x =   0;
        rect.gBirdyClips[ 0 ].y =   0;
        rect.gBirdyClips[ 0 ].w =  140;
        rect.gBirdyClips[ 0 ].h = 89;

        rect.gBirdyClips[ 1 ].x =  140;
        rect.gBirdyClips[ 1 ].y =   0;
        rect.gBirdyClips[ 1 ].w =  140;
        rect.gBirdyClips[ 1 ].h = 89;
        }
    

	//Load sprite sheet texture
	if (!tex.gSpriteSheetTexture.loadFromFile("Images/love2.png"))
	{
		printf("Failed to load love texture!\n");
		success = false;
	}
	else
	{
		//Set sprite clips

		rect.gSpriteClips[0].x = 0;
		rect.gSpriteClips[0].y = 0;
		rect.gSpriteClips[0].w = 20;
		rect.gSpriteClips[0].h = 20;
	}

	if (!tex.gfoodySheetTexture.loadFromFile("Images/coin.bmp"))
	{
		printf("Failed to load food texture!\n");
		success = false;
	}
	else
	{
		//Set sprite clips

		rect.gfoodyClips[0].x = 0;
		rect.gfoodyClips[0].y = 0;
		rect.gfoodyClips[0].w = 35;
		rect.gfoodyClips[0].h = 35;
	}

	Music.gScratch = Mix_LoadWAV("Music/sound.wav");
	if (Music.gScratch == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	
	Music.gScratch1 = Mix_LoadWAV("Music/sound2.wav");
	if (Music.gScratch1 == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	
	Music.gScratch2 = Mix_LoadWAV("Music/over.wav");
	if (Music.gScratch2 == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

        Music.gMusic = Mix_LoadMUS("Music/music1.mp3");
	if (Music.gMusic == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	
	Music.gMusic1 = Mix_LoadMUS("Music/hit.mp3");
	if (Music.gMusic1 == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}
	return success;
}

int loadhighscore()
{

	SDL_Surface *image = SDL_LoadBMP("Images/score.bmp");
	SDL_Texture *texture = SDL_CreateTextureFromSurface(app.gRenderer, image);
	
	FILE *fPtr;
	long long int a[3];
	char p[10000];
	int i = 0;
	fPtr = fopen("Images/highscore.txt", "r");

	while (fscanf(fPtr, "%lld", &a[i]) == 1)
	{
		i++;
		if (i == 3)
			break;
	}
	fclose(fPtr);

	sprintf(p,"%lld  %lld  %lld",a[0],a[1],a[2]);
	int ll=strlen(p);
	p[ll-1]='\0';

	SDL_Color textColor = {0, 48, 96, 255};

	while (1)
	{
		SDL_RenderCopy(app.gRenderer, texture, NULL, NULL);
		SDL_Event e;
		int x, y;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				return 0;
			
			if (e.type == SDL_KEYDOWN)
			{
				//Adjust the velocity
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					return -1;
				}
			}
		}
		for(int m = 0 ; m < 3 ; m++)
		{
		timeText.str(" ");

		timeText << "" << m+1 << " ...........  " << a[m];
		if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor))
		{
			printf("Unable to render time texture!\n");
		}
		gTimeTextTexture.render(190, ((SCREEN_HEIGHT - gPromptTextTexture.getHeight()) / 2.9)+50+(m*100));

		}
		SDL_RenderPresent(app.gRenderer);
		SDL_Delay(15);
	}
	    
	return 3;
}

int loadinstructions(){

    SDL_Surface *image = SDL_LoadBMP("Images/Ins1.bmp");
	SDL_Texture *texture = SDL_CreateTextureFromSurface(app.gRenderer, image);
	
	while (1)
	{
		SDL_RenderCopy(app.gRenderer, texture, NULL, NULL);
		SDL_Event e;
		int x, y;
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
				return 0;
			
			if (e.type == SDL_KEYDOWN)
			{
				//Adjust the velocity
				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					return -1;
				}
			}
		}
		SDL_RenderPresent(app.gRenderer);
		SDL_Delay(15);
	}

	return 2;
}
