#include "obstacle.h"
#include "defs.h"
#include "math.h"
#include "main.h"
#include <SDL.h>

Obstacle aObstacles[MAX_OBSTACLES] = { NULL };

void obstacle_placeFloor(void){

    // amount of cubes to place
    int nCount = WIDTH / SIZE + 1;

    for (int i = 0; i < nCount; i++){
        int nX = i*SIZE;
        int nY = HEIGHT-SIZE;

        aObstacles[i].bIsAlive = true;
        aObstacles[i].fVelX = SPEED;
        aObstacles[i].rRegion = (SDL_Rect) {nX,nY,SIZE,SIZE};
        aObstacles[i].sColor = hexToColor(0xAAAAAAFF);
    }

    SDL_Log("Placed down a floor of %d cubes",nCount);
    
}

bool obstacle_overlaps(const SDL_Rect *rect){
    return false;
}

void obstacle_update(float delta){

}

void obstacle_draw(App *app){
    for (int i = 0; i < MAX_OBSTACLES; i++){
        if (aObstacles[i].bIsAlive == NULL || aObstacles[i].bIsAlive == false) continue;

        SDL_Color *sCol = &aObstacles[i].sColor;
        SDL_Rect *rRegion = &aObstacles[i].rRegion; 

        csc(SDL_SetRenderDrawColor(app->renderer,sCol->r,sCol->g,sCol->b,sCol->a));
        csc(SDL_RenderFillRect(app->renderer,rRegion));
    }
}
