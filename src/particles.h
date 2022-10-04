#ifndef PARTICLES_H
#define PARTICLES_H

#define MAX_PARTICLES 16384

#include "main.h"

typedef struct {
    bool bIsAlive;
    float fLifetime;
    SDL_FPoint v2Velocity; 
    SDL_FRect rRegion;
    SDL_Color sColor;
} Particle;

int particles_spawn(SDL_FPoint *pos, SDL_FPoint *vel,
        float lifetime, float size, SDL_Color *col);

void particles_draw(App *app);
void particles_update(float delta);

#endif // PARTICLES_H
