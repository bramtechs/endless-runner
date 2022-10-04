#include "obstacle.h"
#include "defs.h"
#include "math.h"
#include "main.h"

Obstacle aObstacles[MAX_OBSTACLES] = { false };
float fOffsetX = 0.0f;
float fSpawnTimer = 3.0f;
float fPrevInterval = 0.0f;

SDL_Color sPowerColor = { NULL };

void obstacle_init(void){

    // generate color
    sPowerColor = hexToColor(0xFFBB00FF);

    // amount of cubes to place
    int nCount = WIDTH / SIZE + 5;

    for (int i = 0; i < nCount; i++){
        int nX = i;
        int nY = HEIGHT/SIZE-1;
        int j = obstacle_place(nX,nY,i);
        aObstacles[j].bIsFloor = true;
        aObstacles[j].rRegion.w += 10; // hide gaps
    }
    SDL_Log("Placed down a floor of %d cubes",nCount);
}

int obstacle_place(float x, float y, int index){
    // find empty obstacle
    for (int i = 0; i < MAX_OBSTACLES; i++){
        if (aObstacles[i].bIsAlive == true) continue;

        float nX = x*SIZE;
        float nY = y*SIZE;
        SDL_Color sCol = i % 2 == 0 ? hexToColor(0xAAAAAAFF):hexToColor(0xBBBBBBFF);

        // initalize new obstacle
        aObstacles[i].bIsAlive = true;
        aObstacles[i].bIsFloor = false;
        aObstacles[i].bHasPower = false;
        aObstacles[i].rRegion = (SDL_FRect) {nX,nY,SIZE,SIZE};
        
        float fMargin = 20;
        aObstacles[i].rPowerup = (SDL_FRect) {nX+fMargin,nY-SIZE*2.0f,SIZE-fMargin*2.0f,SIZE-fMargin*2.0f};
        aObstacles[i].sColor = sCol;
        aObstacles[i].sPowerColor = sPowerColor;
        return i;
    }
    SDL_LogError(1,"Max obstacle count reached!");
    return 0;
}

bool obstacle_overlaps(const SDL_FRect *rect){
    for (int i = 0; i < MAX_OBSTACLES; i++){
        if (aObstacles[i].bIsAlive == false) continue;
        if (aObstacles[i].bIsFloor == true) continue;

        SDL_FRect *rRegion = &aObstacles[i].rRegion; 
        // TODO this is awful, implement own function
        SDL_Rect rA = FRectToRect(rRegion);
        SDL_Rect rB = FRectToRect(rect);
        if (SDL_HasIntersection(&rA, &rB)){
            return true;
        }
    }
    return false;
}

bool obstacle_overlaps_floor(const SDL_FRect *rect, float *snapY){
    for (int i = 0; i < MAX_OBSTACLES; i++){
        if (aObstacles[i].bIsAlive == false) continue;
        if (aObstacles[i].bIsFloor == false) continue;

        SDL_FRect *rRegion = &aObstacles[i].rRegion; 
        // TODO this is awful, implement own function
        SDL_Rect rA = FRectToRect(rRegion);
        SDL_Rect rB = FRectToRect(rect);
        if (SDL_HasIntersection(&rA, &rB)){
            *snapY = rRegion->y;
            return true;
        }
    }
    *snapY = 0.0f;
    return false;
}

bool obstacle_overlaps_power(const SDL_FRect *rect){
    for (int i = 0; i < MAX_OBSTACLES; i++){
        if (aObstacles[i].bIsAlive == false) continue;
        if (aObstacles[i].bIsFloor == true) continue;
        if (aObstacles[i].bHasPower == false) continue;

        SDL_FRect *rRegion = &aObstacles[i].rPowerup; 
        // TODO this is awful, implement own function
        SDL_Rect rA = FRectToRect(rRegion);
        SDL_Rect rB = FRectToRect(rect);
        if (SDL_HasIntersection(&rA, &rB)){
            SDL_Log("touches");
            return true;
        }
    }
    return false;
}


void obstacle_update(float delta){
    float fDeltaX = SPEED*delta;

    // move all the obstacles to the left
    for (int i = 0; i < MAX_OBSTACLES; i++){
        if (aObstacles[i].bIsAlive == false) continue;
        Obstacle *sObs = &aObstacles[i];

        if (sObs->bIsFloor) {
            sObs->rRegion.x = fOffsetX+i*SIZE;
        }
        else {
            sObs->rRegion.x -= fDeltaX;
            sObs->rPowerup.x -= fDeltaX;

            if (sObs->rRegion.x < -20 - SIZE) {
			    sObs->bIsAlive = false;
			    SDL_Log("Cleaned up block");
            }
        }
    }

    // optical illusion
    fOffsetX -= fDeltaX;
    if (fOffsetX < -SIZE * 2) {
        fOffsetX += SIZE * 2;
    }

    // spawn blocks
    if (fSpawnTimer < 0.0f){
        float fRNG = rand()%3+0.3f;
        fSpawnTimer += fRNG; // TODO random

        SDL_Log("Spawned obstacle. Next in %fs...",fSpawnTimer);
        int i = obstacle_place(WIDTH/SIZE+5,HEIGHT/SIZE-2,1);

        aObstacles[i].bHasPower = fRNG < 0.8f || fPrevInterval < 0.8f;

        fPrevInterval = fRNG;
    }
    fSpawnTimer -= delta;
}

void obstacle_draw(App *app){
    for (int i = 0; i < MAX_OBSTACLES; i++){
        if (aObstacles[i].bIsAlive == false) continue;

        SDL_Color *sCol = &aObstacles[i].sColor;
        csc(SDL_SetRenderDrawColor(app->renderer,sCol->r,sCol->g,sCol->b,sCol->a));

        SDL_FRect *rRegion = &aObstacles[i].rRegion; 
        SDL_Rect rRect = FRectToRect(rRegion);
        csc(SDL_RenderFillRect(app->renderer,&rRect));

        if (!aObstacles[i].bIsFloor && aObstacles[i].bHasPower) {
            SDL_Color *sPowerCol = &aObstacles[i].sPowerColor;
            csc(SDL_SetRenderDrawColor(app->renderer,sPowerCol->r,sPowerCol->g,sPowerCol->b,sPowerCol->a));

            SDL_FRect *rPowerup = &aObstacles[i].rPowerup; 
            SDL_Rect rPowerRect = FRectToRect(rPowerup);
            csc(SDL_RenderFillRect(app->renderer,&rPowerRect));
        }
    }
}
