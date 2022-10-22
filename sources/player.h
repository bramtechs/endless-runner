//
// Created by bram on 10/22/22.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "stdbool.h"
#include "raylib.h"

typedef struct {
    float gravity;
    float jumpForce;
    float stompForce;
    float opacity;
    Rectangle region;
    Vector2 vel;
    Color color;
    Color trailColor;
    bool isAlive;
} Player;

#define SIZE 50
#define GRAVITY 20.0f
#define JUMP_FORCE 10.0f
#define STOMP_FORCE 15.0f

Player player_init(void);

void player_update(Player *pl, float delta);

void player_draw(Player *pl);

void player_stomp(Player *pl);

void player_move(Player *pl, Vector2 *offset);

bool player_grounded(Player *pl);

#endif //PLAYER_H
