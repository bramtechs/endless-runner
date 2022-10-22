#include "fade.h"
#include "main.h"
#include "defs.h"

float fOpacity = 0.0;
bool bFadeIsRunning = false;
SDL_Rect rScreen = {NULL};

void fade_init(void){
    fOpacity = -50.0;
    bFadeIsRunning = false;
    rScreen = (SDL_Rect){0.0, 0.0, WIDTH, HEIGHT};
}

void fade_run(void){
    if (!bFadeIsRunning){
        fade_init();
        bFadeIsRunning = true;
    }
}

void fade_update(float delta){
    if (bFadeIsRunning){
        if (fOpacity < 255.0){
            fOpacity += delta*60.0;
        }else{
            fOpacity = 255.0;
        }
    }else {
        fOpacity = -50.0;
    }
}

void fade_draw(App *app){
    Uint8 o = clamp((int)fOpacity,0,255);
    SDL_Color sCol = (SDL_Color) { 0, 0, 0, o };
    csc(SDL_SetRenderDrawColor(app->renderer,sCol.r,sCol.g,sCol.b,sCol.a));
    csc(SDL_RenderFillRect(app->renderer,&rScreen));
}
