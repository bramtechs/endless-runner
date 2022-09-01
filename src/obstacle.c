#include "obstacle.h"
#include "defs.h"
#include "math.h"
#include "main.h"
#include <SDL.h>

Obstacle aObstacles[MAX_OBSTACLES] = { false };
float fOffsetX = 0.0f;

void obstacle_placeFloor(void){

    // amount of cubes to place
    int nCount = WIDTH / SIZE + 4;

    for (int i = 0; i < nCount; i++){
        int nX = i*SIZE;
        int nY = HEIGHT-SIZE;
        SDL_Color sCol = i % 2 == 0 ? hexToColor(0xAAAAAAFF):hexToColor(0xBBBBBBFF);

        // initalize new obstacle
        aObstacles[i].bIsAlive = true;
        aObstacles[i].bIsFloor = true;
        aObstacles[i].rRegion = (SDL_Rect) {nX,nY,SIZE,SIZE};
        aObstacles[i].sColor = sCol;
    }

    SDL_Log("Placed down a floor of %d cubes",nCount);
    
}

bool obstacle_overlaps(const SDL_Rect *rect){
    for (int i = 0; i < MAX_OBSTACLES; i++){
        if (aObstacles[i].bIsAlive == false) continue;

        SDL_Rect *rRegion = &aObstacles[i].rRegion; 
        if (SDL_HasIntersection(rRegion, rect)){
            return true;
        }
    }
    return false;
}

void obstacle_update(float delta){
    // move all the obstacles to the left
    for (int i = 0; i < MAX_OBSTACLES; i++){
        if (aObstacles[i].bIsAlive == false) continue;

        Obstacle *sObs = &aObstacles[i];

        sObs->rRegion.x = (i+fOffsetX)*SIZE;
    }

    // statisfying optical illusion
    if (fOffsetX < -2.0f){
        fOffsetX += 2.0f;
    }

    fOffsetX -= delta*SPEED;
}

void obstacle_draw(App *app){
    for (int i = 0; i < MAX_OBSTACLES; i++){
        if (aObstacles[i].bIsAlive == false) continue;

        SDL_Color *sCol = &aObstacles[i].sColor;
        SDL_Rect *rRegion = &aObstacles[i].rRegion; 

        csc(SDL_SetRenderDrawColor(app->renderer,sCol->r,sCol->g,sCol->b,sCol->a));
        csc(SDL_RenderFillRect(app->renderer,rRegion));
    }
}
