//
// Created by bram on 10/22/22.
//
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include "obstacle.h"
#include "main.h"

ObstacleWorld obstacle_init(void) {
    ObstacleWorld world = (ObstacleWorld) {
            .isRunning = true,
            .size = 64.0f,
            .floorSpeed = 6.0f,
            .speed = 500.0f,
            .powerupColor = GetColor(0xFFBB00FF),
            .color = GetColor(0xAAAAAAFF),
            .colorAlt = GetColor(0xBBBBBBFF),
    };
    // TODO prevent copying data

    int count = SCREEN_WIDTH / world.size + 5;

    for (int x = 0; x < count; x++) {
        int y = SCREEN_HEIGHT / world.size - 1;
        Vector2 pos = (Vector2) {(float) x, (float) y};
        int j = obstacle_place(&world, &pos, x);
        world.obstacles[j].isFloor = true;
        world.obstacles[j].region.width += 10; // hide gaps
    }

    TraceLog(LOG_INFO, "Placed down a floor of %d cubes", count);
    return world;
}

void obstacle_stop(ObstacleWorld *wo) {
    wo->isRunning = false;
    TraceLog(LOG_INFO, "Stopping obstacles!");
}

void obstacle_run(ObstacleWorld *wo, float delta) {
    float offsetX = wo->speed * delta;

    for (int i = 0; i < OBSTACLE_COUNT; i++) {
        if (wo->obstacles[i].isActive) {
            Obstacle *obs = &wo->obstacles[i];
            if (obs->isFloor) {
                float size = wo->size;
                obs->region.x = offsetX + (float) i * size;
            } else {
                obs->region.x -= offsetX;
                obs->powerup.region.y -= offsetX;

                // cleanup when offscreen
                if (obs->region.x < -20 - wo->size) {
                    obs->isActive = false;
                    TraceLog(LOG_INFO, "Cleaned up block");
                }
            }
        }
    }
}

void obstacle_update(ObstacleWorld *wo, float delta) {
    if (wo->isRunning) {
        obstacle_run(wo, delta);
    }
}


void obstacle_draw(ObstacleWorld *wo) {
    for (int i = 0; i < OBSTACLE_COUNT; i++) {
        Obstacle *obs = &wo->obstacles[i];
        if (obs->isActive) {
            DrawRectangleRec(obs->region, obs->color);
            if (!obs->isFloor && obs->hasPower) {
                DrawRectangleRec(obs->powerup.region, obs->powerup.color);
            }
        }
    }
}

int obstacle_place(ObstacleWorld *wo, Vector2 *pos, int index) {
    // find empty obstacle slot
    for (int i = 0; i < OBSTACLE_COUNT; i++) {
        Obstacle *obs = &wo->obstacles[i];
        if (wo->obstacles[i].isActive == false) {
            float x = pos->x * wo->size;
            float y = pos->y * wo->size;

            Color col = index % 2 == 0 ? wo->color : wo->colorAlt;
            Rectangle region = (Rectangle) {x, y, wo->size, wo->size};

            // initialize new obstacle
            obs->isActive = true;
            obs->isFloor = false;
            obs->hasPower = false;
            obs->region = region;
            obs->color = col;

            // initialize powerup on top
            float margin = 20;
            obs->powerup.region = (Rectangle) {x + margin, y - wo->size * 2.0f, wo->size - margin * 2.0f,
                                               wo->size - margin * 2.0f};
            obs->powerup.color = wo->powerupColor;
            return i;
        }
    }
    TraceLog(LOG_ERROR, "Max obstacle count reached!");
    return 0;
}

bool obstacle_overlaps(ObstacleWorld *wo, Rectangle *rect, ObstacleType type) {
    for (int i = 0; i < OBSTACLE_COUNT; i++) {
        Obstacle *obstacle = &wo->obstacles[i];
        if (obstacle->isActive) {
            bool relevant = false;
            Rectangle *region;
            switch (type) {
                case BLOCK:
                    region = &obstacle->region;
                    relevant = !obstacle->isFloor;
                    break;
                case FLOOR:
                    region = &obstacle->region;
                    relevant = obstacle->isFloor;
                    break;
                case POWERUP:
                    region = &obstacle->powerup.region;
                    relevant = !obstacle->isFloor && obstacle->hasPower;
                    break;
                default:
                    assert(false);
            }

            if (relevant && CheckCollisionRecs(*region, *rect)) {
                return true;
            }
        }
    }
    return false;
}
