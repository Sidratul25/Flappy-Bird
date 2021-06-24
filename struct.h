#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include "defs.h"

#include <bits/stdc++.h>
using namespace std;


//The music that will be played
struct A{
Mix_Music *gMusic = NULL;
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gScratch1 = NULL;
} Music;

struct B{
//The window we'll be rendering to
SDL_Window *gWindow = NULL ;
//Globally used font
TTF_Font *gFont = NULL;
//The window renderer
SDL_Renderer *gRenderer = NULL ;
} app;

struct C{
SDL_Rect wall[10];
SDL_Rect love[1];
SDL_Rect food[1];
SDL_Rect gSpriteClips[parts];
SDL_Rect gfoodyClips[foody];
SDL_Rect gBirdyClips[ FLYING_ANIMATION_FRAMES ];
} rect;

