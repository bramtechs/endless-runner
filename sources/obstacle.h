//
// Created by bram on 10/22/22.
//

#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <stdbool.h>
#include "raylib.h"

#define OBSTACLE_COUNT (64)

typedef enum {
    BLOCK,
    FLOOR,
    POWERUP
} ObstacleType;

typedef struct {
    Rectangle region;
    Color color;
} Powerup;

typedef struct {
    bool isActive;
    bool isFloor;
    bool hasPower;
    Color color;
    Rectangle region;
    Powerup powerup;
} Obstacle;

typedef struct {
    bool isRunning;
    float size;
    float floorSpeed;
    float speed;
    Obstacle obstacles[OBSTACLE_COUNT];
    Color powerupColor;
    Color color;
    Color colorAlt;
} ObstacleWorld;

#include "stdbool.h"
#include "raylib.h"

ObstacleWorld obstacle_init(void);

void obstacle_update(ObstacleWorld *wo, float delta);

void obstacle_draw(ObstacleWorld *wo);

void obstacle_stop(ObstacleWorld *wo);

int obstacle_place(ObstacleWorld *wo, Vector2 *pos, int index);

bool obstacle_overlaps(ObstacleWorld *wo, Rectangle *rect, ObstacleType type);

#endif //OBSTACLE_H