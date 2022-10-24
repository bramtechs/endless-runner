//
// Created by bram on 10/24/22.
//

#ifndef PARTICLES_H
#define PARTICLES_H

#include <stdbool.h>
#include "raylib.h"

#define MAX_PARTICLES (8192)

typedef struct {
    bool isAlive;
    float lifetime;
    Vector2 velocity;
    Rectangle region;
    Color color;
} Particle;

typedef struct {
    Particle particles[MAX_PARTICLES];
} ParticleWorld ;

ParticleWorld particle_init(void);

Particle* particle_spawn(ParticleWorld *pw, Vector2 *pos, Vector2 *vel, float lifetime, float size, Color *color);

void particle_update(ParticleWorld *pw, float delta);

void particle_draw(ParticleWorld *pw);

#endif //PARTICLES_H