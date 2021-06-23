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

int username()
{

    SDL_Event e;
    //Set text color as black
    SDL_Color textColor = {206, 255, 243, 255};
    if (x == USERNAME)
    {
        //Karim.init();
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }

        else if (e.type == SDL_KEYDOWN)
        {
            //Handle backspace
            if (e.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0)
            {
                //lop off character
                inputText.pop_back();
                renderText = true;
            }
            //Handle copy
            else if (e.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
            {
                SDL_SetClipboardText(inputText.c_str());
            }
            //Handle paste
            else if (e.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
            {
                inputText = SDL_GetClipboardText();
                renderText = true;
            }
        }
        //Special text input event
        else if (e.type == SDL_TEXTINPUT)
        {
            //Not copy or pasting
            if (!(SDL_GetModState() & KMOD_CTRL && (e.text.text[0] == 'c' || e.text.text[0] == 'C' || e.text.text[0] == 'v' || e.text.text[0] == 'V')))
            {
                //Append character
                inputText += e.text.text;
                renderText = true;
            }
        }

        if (x == USERNAME)
        {
            //Mix_HaltMusic();
            if (e.key.keysym.sym == SDLK_ESCAPE)
            {
                cout << "Back To Menu" << endl;
                x = play();
            }
            else if (e.key.keysym.sym == SDLK_RETURN)
            {
                x = loadmenu();
            }
            if (renderText)
            {
                //Text is not empty
                if (inputText != "")
                {
                    //Render new text
                    gInputTextTexture.loadFromRenderedText(inputText.c_str(), textColor);
                }
                //Text is empty
                else
                {
                    //Render space texture
                    gInputTextTexture.loadFromRenderedText(" ", textColor);
                }
            }

            //Clear screen
            SDL_SetRenderDrawColor(app.gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
            SDL_RenderClear(app.gRenderer);
            tex.gUBGTexture.render(0, 0);
            tex.gUBGTexture.render(tex.gUBGTexture.getWidth(), 0);
            //Render text textures
            //gPromptTextTexture.render( ( SCREEN_WIDTH - gPromptTextTexture.getWidth() ) / 2, 0 );
            gInputTextTexture.render((SCREEN_WIDTH - gInputTextTexture.getWidth()) / 2, (SCREEN_HEIGHT - gInputTextTexture.getHeight()) / 2);

            //Update screen
            SDL_RenderPresent(app.gRenderer);
        }
        //dot.handleEvent(e);
    }
}

int play()
{

    SDL_Event e;
    //Set text color as black
    SDL_Color textColor = {206, 255, 243, 255};
    //The dot that will be moving around on the screen
    Dot dot;
    SDL_Color pillar = {0, 128, 0, 255};
    double scrollingOffset = 0;
    int scroll = 0, changecolori[6], changecolorj[6], changecolork[6];
    double loveWidth = 900, loveHeight = 350;
    double foodWidth = SCREEN_WIDTH + 350, foodHeight = 250;

    memset(changecolori, 0, sizeof(changecolori));
    memset(changecolorj, 0, sizeof(changecolorj));
    memset(changecolork, 0, sizeof(changecolork));
    double scrollspeed = 2;

    rect.wall[0].x = SCREEN_WIDTH + 20;
    rect.wall[0].y = 0;
    rect.wall[0].w = 40;
    rect.wall[0].h = 170;

    rect.wall[1].x = SCREEN_WIDTH + 220;
    rect.wall[1].y = SCREEN_HEIGHT - rect.wall[1].h;
    rect.wall[1].w = 35;
    rect.wall[1].h = 130;

    rect.wall[2].x = SCREEN_WIDTH + 430;
    rect.wall[2].y = SCREEN_HEIGHT - rect.wall[2].h;
    rect.wall[2].w = 50;
    rect.wall[2].h = 200;

    rect.wall[3].x = SCREEN_WIDTH + 590;
    rect.wall[3].y = 60;
    rect.wall[3].w = 27;
    rect.wall[3].h = 60;

    rect.wall[4].x = SCREEN_WIDTH + 300;
    rect.wall[4].y = 0;
    rect.wall[4].w = 50;
    rect.wall[4].h = 140;

    int liferecheck = 0;
    int frame = 0;
    dot.mPosX = dot.mPosY = dot.mVelX = dot.mVelY = 0;
    score = 0;
    life = 0, checklife = 0, noncollied = -1;
    quit = false;
    while (!quit)
    {
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            dot.handleEvent(e);
        }

        for (int now = 0; now < 5; now++)
        {
            dot.move(rect.wall[now]);
        }

        dot.move(rect.food[0]);
        dot.move(rect.love[0]);

        if (checklife > 0 && liferecheck == 0)
        {
            life++;
            liferecheck = 1;
        }

        if (life < 0)
        {
            loadscoreboard();
            quit = true;
            x = 5;
            Mix_HaltMusic();
            break;
        }
        //Scroll background
        scrollingOffset -= scrollspeed;

        for (int now = 0; now < 5; now++)
        {
            rect.wall[now].x -= scrollspeed;
        }

        foodWidth -= scrollspeed;
        loveWidth -= scrollspeed;

        if (loveWidth <= -20)
        {
            loveWidth = 1800;
            loveHeight += 100;
            rect.gSpriteClips[0].w = 20;
            rect.gSpriteClips[0].h = 20;
            if (loveHeight >= 390)
                loveHeight = 80;
        }

        if (foodWidth <= -30)
        {
            foodWidth = 1200;
            if (foodHeight >= 80)
                foodHeight -= 30;
            else
                foodHeight = 350;
            rect.gfoodyClips[0].w = 35;
            rect.gfoodyClips[0].h = 35;
        }
        if (scrollingOffset < -tex.gBGTexture.getWidth())
        {
            scrollingOffset = 0;
            scroll++;
            liferecheck = 0;
        }

        for (int i = 0; i <= 4; i++)
        {

            if (rect.wall[i].x <= -70)
            {
                if (i == noncollied)
                    noncollied = -1;
                if (i != 5)
                    rect.wall[i].x = SCREEN_WIDTH;
                else
                {
                    rect.wall[i].x = SCREEN_WIDTH + 1400;
                    rect.wall[i].h = 14;
                    rect.wall[i].w = 14;
                }
                if (i == 3)
                {
                    rect.wall[i].y -= 60;
                    if (rect.wall[i].w < 70)
                        rect.wall[i].w += 3;
                    else
                        rect.wall[i].w = 40;
                    if (rect.wall[i].h > 60)
                        rect.wall[i].h -= 40;
                    else
                        rect.wall[i].h = 150;
                    if (rect.wall[3].y <= 0)
                        rect.wall[3].y = 250;
                }

                if (i % 2 == 0)
                {
                    if (rect.wall[i].w < 70)
                        rect.wall[i].w += 3;
                    else
                        rect.wall[i].w = 30;
                    if (rect.wall[i].h > 60)
                        rect.wall[i].h -= 40;
                    else
                        rect.wall[i].h = 200;
                    if (i == 2)
                        rect.wall[i].y = SCREEN_HEIGHT - rect.wall[i].h;
                }
                else if (i == 1)
                {
                    if (rect.wall[i].w < 60)
                        rect.wall[i].w += 3;
                    else
                        rect.wall[i].w = 40;
                    if (rect.wall[i].h > 60)
                        rect.wall[i].h -= 40;
                    else
                        rect.wall[i].h = 200;
                    rect.wall[i].y = SCREEN_HEIGHT - rect.wall[i].h;
                }
                else if (i == 5)
                {
                    if (rect.wall[i].y >= 60)
                        rect.wall[i].y -= 50;
                    else
                        rect.wall[i].y = 350;
                }
                int j = rect.wall[i].h - rect.wall[i + 1].h;
                if (j < 0)
                    j = -j;
                if (j <= 70)
                {
                    if (i == 2)
                    {
                        rect.wall[i].h = 130;
                        rect.wall[i].y = SCREEN_HEIGHT - rect.wall[i].h;
                    }
                    else if (i != 5)
                    {
                        rect.wall[i].h = 130;
                    }
                }
                else if (j > 100)
                {
                    if (i == 2 || i == 1)
                    {
                        rect.wall[i].h = 130;
                        rect.wall[i].y = SCREEN_HEIGHT - rect.wall[i].h;
                    }
                    else if (i != 3 && i != 5)
                    {
                        rect.wall[i].h = 130;
                    }
                }
                changecolori[i] += 60;
                changecolorj[i] += 80;
                changecolork[i] += 50;
                if (changecolori[i] >= 400)
                {
                    changecolori[i] = 0;
                    changecolorj[i] = 0;
                    changecolork[i] = 0;
                }
            }
        }
        SDL_SetRenderDrawColor(app.gRenderer, 0, 128, 0, 255);
        tex.gBGTexture.render(scrollingOffset, 0);
        tex.gBGTexture.render(scrollingOffset + tex.gBGTexture.getWidth(), 0);
        dot.render();

        SDL_RenderDrawRect(app.gRenderer, &rect.wall[0]);
        SDL_RenderFillRect(app.gRenderer, &rect.wall[0]);

        SDL_SetRenderDrawColor(app.gRenderer, 0, 128, 0, 255);
        SDL_RenderDrawRect(app.gRenderer, &rect.wall[1]);
        SDL_RenderFillRect(app.gRenderer, &rect.wall[1]);

        SDL_SetRenderDrawColor(app.gRenderer, 0, 128, 0, 255);
        SDL_RenderDrawRect(app.gRenderer, &rect.wall[2]);
        SDL_RenderFillRect(app.gRenderer, &rect.wall[2]);

        SDL_SetRenderDrawColor(app.gRenderer, 0, 128, 0, 255);
        SDL_RenderDrawRect(app.gRenderer, &rect.wall[3]);
        SDL_RenderFillRect(app.gRenderer, &rect.wall[3]);

        SDL_SetRenderDrawColor(app.gRenderer, 0, 128, 0, 255);
        SDL_RenderDrawRect(app.gRenderer, &rect.wall[4]);
        SDL_RenderFillRect(app.gRenderer, &rect.wall[4]);

        SDL_SetRenderDrawColor(app.gRenderer, 0, 128, 0, 255);
        SDL_RenderDrawRect(app.gRenderer, &rect.wall[5]);
        SDL_RenderFillRect(app.gRenderer, &rect.wall[5]);
        //Render textures
        gTimeTextTexture.render(180, (SCREEN_HEIGHT - gPromptTextTexture.getHeight()) / 20);

        SDL_Rect *currentClip = &rect.gSpriteClips[0];
        tex.gSpriteSheetTexture.render(loveWidth, 60 + loveHeight, currentClip);

        SDL_Rect *idontknowClip = &rect.gfoodyClips[0];
        tex.gfoodySheetTexture.render(foodWidth, foodHeight, idontknowClip);

        SDL_RenderPresent(app.gRenderer);

        for (int k = 1; k < scrollspeed; k++)
        {
            score++;
            timeText.str("");
            timeText << "Score:" << score;
            timeText << "   Life:" << life;
        }
        if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor))
        {
            printf("Unable to render time texture!\n");
        }

        rect.love[0].x = loveWidth;
        rect.love[0].y = loveHeight + 60;
        rect.love[0].w = rect.gSpriteClips[0].w;
        rect.love[0].h = rect.gSpriteClips[0].h;

        rect.food[0].x = foodWidth;
        rect.food[0].y = foodHeight;
        rect.food[0].w = rect.gfoodyClips[0].w;
        rect.food[0].h = rect.gfoodyClips[0].h;

        scrollspeed += 0.005;
    }
}
