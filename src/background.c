#include "background.h"
#include "defs.h"
#include "math.h"
#include "main.h"
#include <assert.h>

BGLayer aLayers[BG_LAYER_COUNT];

void background_init(){
   for (int i = 0; i < BG_LAYER_COUNT; i++){
        background_initLayer(i);
   }
}

void background_initLayer(int index){

    // get and assign the new background layer
    BGLayer *sLayer = &(aLayers[index]);
    sLayer->fSpeed = BG_SPEED*index+5.0f;

    float fPerc = (BG_LAYER_COUNT-index)/(float)BG_LAYER_COUNT;
    SDL_Log("perc: %f",fPerc);
    int nPenX = 0.0f;
    int nColumn = 0;
    while (nPenX < WIDTH){
        int nWidth = randIntRange(BG_WIDTH_MIN,BG_WIDTH_MAX);
        int nHeight = randIntRange(BG_HEIGHT_MIN,BG_HEIGHT_MAX)*fPerc;

        // set building dimensions 
        SDL_FRect *rRect = &(sLayer->aRects[nColumn]);
        rRect->x = nPenX;
        rRect->y = HEIGHT-nHeight;
        rRect->w = nWidth;
        rRect->h = nHeight;

        // set building color
        SDL_Color *sCol = &(sLayer->aColors[nColumn]);
        sCol->r = randIntRange(80,180);
        sCol->g = randIntRange(80,180);
        sCol->b = randIntRange(80,180);
        sCol->a = 255;

        nPenX += nWidth;
        nColumn++;

        assert(nColumn < BG_MAX); // Exceeding max column amount for background! 
    }

    sLayer->nCount = nColumn;
}

void background_update(float delta){
    for (int i = 0; i < BG_LAYER_COUNT; i++){
        BGLayer *sLayer = &(aLayers[i]);
        for (int j = 0; j < sLayer->nCount; j++){
            SDL_FRect *rRect = &(sLayer->aRects[j]);
            rRect->x -= sLayer->fSpeed*delta;

            // wrap building around
            if (rRect->x < -rRect->w){
                rRect->x = WIDTH; 
            }
        }
    }
}

void background_draw(App *app){
    for (int i = 0; i < BG_LAYER_COUNT; i++){
        BGLayer *sLayer = &(aLayers[i]);
        for (int j = 0; j < sLayer->nCount; j++){
            SDL_Color *sCol = &(sLayer->aColors[j]);;
            csc(SDL_SetRenderDrawColor(app->renderer,sCol->r,sCol->g,sCol->b,sCol->a));

            SDL_FRect *rRect = &(sLayer->aRects[j]);
            SDL_Rect rRegion = FRectToRect(rRect);
            csc(SDL_RenderFillRect(app->renderer,&rRegion));
        }
    }
}
