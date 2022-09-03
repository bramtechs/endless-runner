#include "particles.h"
#include "math.h"
#include <assert.h>
#include "main.h"

Particle aParticles[MAX_PARTICLES] = { false };
int nParticleCount;

int particles_spawn(SDL_FPoint *pos, SDL_FPoint *vel,
        float lifetime, float size, SDL_Color *col){

    // check for free slot
    for (int i = 0; i < MAX_PARTICLES; i++){
        Particle *fPart = &aParticles[i];
        if (fPart->bIsAlive == true) continue;

        fPart->bIsAlive = true; 
        fPart->fLifetime = lifetime; 
        fPart->v2Velocity = *vel; 
        fPart->sColor = *col; 

        // calculate region box
        float nX = pos->x - size*0.5f;
        float nY = pos->y - size*0.5f;
        fPart->rRegion = (SDL_FRect) { nX, nY, size, size }; 

        //SDL_Log("%i particles",nParticleCount);
        nParticleCount++;
        return;
    }
    SDL_Log("Not enough particles");
}

void particles_update(float delta){
    for (int i = 0; i < MAX_PARTICLES; i++){
        Particle *fPart = &(aParticles[i]);
        if (fPart->bIsAlive == false) continue;

        fPart->rRegion.x += fPart->v2Velocity.x*delta;
        fPart->rRegion.y += fPart->v2Velocity.y*delta;

        // die after a while
        fPart->fLifetime -= delta;
        if (fPart->fLifetime < 0.0f){
            fPart->bIsAlive = false;
            nParticleCount--;
        }
    }
}

void particles_draw(App *app){
    for (int i = 0; i < MAX_PARTICLES; i++){
        Particle *fPart = &(aParticles[i]);
        if (fPart->bIsAlive == false) continue;

        SDL_Color *sCol = &(fPart->sColor);
        csc(SDL_SetRenderDrawColor(app->renderer,sCol->r,sCol->g,sCol->b,sCol->a));

        SDL_FRect *rRegion = &(fPart->rRegion);
        SDL_Rect rRect = FRectToRect(rRegion);
        csc(SDL_RenderFillRect(app->renderer,&rRect));
    }
}
