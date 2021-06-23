#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

int x = -1;
//Screen dimension constants
const int SCREEN_WIDTH = 597;
const int SCREEN_HEIGHT = 600;

//Button constants
const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 100;
const int TOTAL_BUTTONS = 4;

const int parts = 1;
const int foody = 1;

int positionx, positiony;

Uint64 startTime = 0;

std::string inputText = "";
bool renderText = false;
int USERNAME = 9;

long long int score;
int life, checklife, noncollied;

const int FLYING_ANIMATION_FRAMES = 2;
int frame = 0;
bool quit = false;
