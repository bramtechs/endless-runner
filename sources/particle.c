//
// Created by bram on 10/24/22.
//
#include <assert.h>
#include "particle.h"

ParticleWorld particle_init(void) {
    ParticleWorld pw = (ParticleWorld) {};
    return pw;
}

Particle *particle_spawn(ParticleWorld *pw, Vector2 *pos, Vector2 *vel, float lifetime, float size, Color *color) {
// find free spot
    for (int i = 0; i < MAX_PARTICLES; i++) {
        Particle *part = &pw->particles[i];
        if (part->isAlive == false) {
            part->isAlive = true;
            part->lifetime = lifetime;
            part->velocity = *vel;
            part->color = *color;

            float x = pos->x - size * 0.5;
            float y = pos->y - size * 0.5;
            part->region = (Rectangle) {x, y, size, size};
            return part;
        }
    }
    TraceLog(LOG_WARNING, "Ran out of particles!");
    return &pw->particles[0];
}

void particle_update(ParticleWorld *pw, float delta) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        Particle *part = &pw->particles[i];
        if (part->isAlive) {
            part->region.x += part->velocity.x * delta;
            part->region.y += part->velocity.y * delta;

            // die after a while
            part->lifetime -= delta;
            if (part->lifetime < 0.0f) {
                part->isAlive = false;
            }
        }
    }
}

void particle_draw(ParticleWorld *pw) {
    for (int i = 0; i < MAX_PARTICLES; i++) {
        Particle *part = &pw->particles[i];
        if (part->isAlive) {
            DrawRectangleRec(part->region, part->color);
        }
    }
}