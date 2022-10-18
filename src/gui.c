#include <stdio.h>
#include <string.h>
#include "gui.h"
#include "main.h"
#include "math.h"

TTF_Font* sFont = {NULL};
float fTimer = 0.0;
bool bIsCounting = true;

void gui_init(App* app){
    TTF_Init();
    sFont = csp(TTF_OpenFont("assets/font.ttf",24));

    SDL_Log("Font loaded");
}

void gui_stop(void){
    bIsCounting = false;
}

void gui_update(float delta){
    if (bIsCounting){
        fTimer += delta*10.0;
    }
}

void gui_draw(App* app){

    int nScore = (int)fTimer;
    char cText[50];
    sprintf(&cText,"%d",nScore);

    // based allocating texture every frame
    SDL_Color sColor = hexToColor(0xFFFFFFFF);
    SDL_Surface* sScoreSurface = TTF_RenderText_Solid(sFont, cText, sColor); 
    SDL_Texture* sScoreTexture = SDL_CreateTextureFromSurface(app->renderer, sScoreSurface);

    // blit text texture
    SDL_Rect sRect;
    sRect.x = 0;
    sRect.y = 0;
    sRect.w = strlen(cText)*50;
    sRect.h = 100;
    SDL_RenderCopy(app->renderer, sScoreTexture, NULL, &sRect);

    SDL_FreeSurface(sScoreSurface);
    SDL_DestroyTexture(sScoreTexture);
}

void gui_dispose(void){
}
