
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <bits/stdc++.h>
#include "defs.h"
#include "struct.h"
#include "texture.cpp"
#include "init.cpp"
#include "dot.cpp"
#include "scoreboard.cpp"
#include "play.cpp"


using namespace std;

int main(int argc, char *args[])
{

	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
        else
		{
		    if(x==-1)
            //The current input text.
            //Set text color as black
			SDL_Color textColor  = { 0, 0, 0, 0xFF };
            

			//Enable text input
			SDL_StartTextInput();
			while (x)
			{
            
                //The rerender text flag
				bool renderText = false;

			    SDL_Event m;
			    kol=0;
				x = loadmenu();				

				if (x == 1 && kol==1)
				{
				   x = username();	
				   x = 9;
				  // x = play();				
                   //x= loadmenu();
                }
				if(x == 9 && kol==1)
				{
					x = play();				
                    x= loadmenu();
				}

				if (x == 2)
				{
					x = loadinstructions();
				}

				if (x == 3)
				{
					x = loadhighscore();
				}
			
		    }
        }

         //Free resources and close SDL
         close();

         return 0;
	}
	
 }

