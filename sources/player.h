//
// Created by bram on 10/22/22.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "stdbool.h"
#include "raylib.h"
#include "obstacle.h"
#include "particle.h"

typedef struct {
    float gravity;
    float jumpForce;
    float stompForce;
    float opacity;
    Rectangle region;
    Vector2 vel;
    Color color;
    bool isAlive;
    bool isGrounded;

    ObstacleWorld* world;
    ParticleWorld* particles;

    float timer;
    float trailInterval;
} Player;

Player player_init(ObstacleWorld *world, ParticleWorld *particles);

void player_update(Player *pl, float delta);

void player_draw(Player *pl);

void player_stomp(Player *pl);

bool player_move(Player *pl, Vector2 *offset);

#endif //PLAYER_H
