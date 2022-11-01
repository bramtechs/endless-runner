//
// Created by bram on 10/22/22.
//
#include <stdbool.h>
#include <assert.h>
#include "obstacle.h"
#include "main.h"

void obstacle_place_floor(ObstacleWorld *wo) {
    // spawn floor blocks
    int count = SCREEN_WIDTH / wo->size + 5;

    for (int x = 0; x < count; x++) {
        int y = SCREEN_HEIGHT / wo->size;
        Vector2 pos = (Vector2) {(float) x, 0.0f};
        int j = obstacle_place(wo, &pos, x);
        wo->obstacles[j].isFloor = true;
        wo->obstacles[j].region.width += 10; // hide gaps
    }
    TraceLog(LOG_INFO, "Placed down a floor of %d cubes", count);
}

ObstacleWorld obstacle_init(void) {
    ObstacleWorld world = (ObstacleWorld) {
            .isRunning = true,

            .size = 64.0f,
            .floorSpeed = 6.0f,
            .speed = 500.0f,

            .spawnTimer = 3,
            .prevSpawnInterval = 0.0f,
            .offsetX = 0.0f,

            .powerupColor = GetColor(0xFFBB00FF),
            .color = GetColor(0xAAAAAAFF),
            .colorAlt = GetColor(0xBBBBBBFF),
    };
    // TODO prevent copying data
    obstacle_place_floor(&world);

    return world;
}

void obstacle_place_block(ObstacleWorld *wo) {
    TraceLog(LOG_INFO, "Spawned obstacle. Next in %fs...", wo->spawnTimer);
    float rng = (float) GetRandomValue(3, 30) * 0.1f;

    Vector2 place = (Vector2) {SCREEN_WIDTH / wo->size + 5, 1};
    int i = obstacle_place(wo, &place, 1);

    wo->obstacles[i].hasPower = rng < 0.8f || wo->prevSpawnInterval < 0.8f;
    wo->prevSpawnInterval = rng;
}

void obstacle_stop(ObstacleWorld *wo) {
    wo->isRunning = false;
    TraceLog(LOG_INFO, "Stopping obstacles!");
}

void obstacle_run(ObstacleWorld *wo, float delta) {
    float scaledDelta = wo->speed * delta;
    wo->offsetX -= scaledDelta;

    for (int i = 0; i < OBSTACLE_COUNT; i++) {
        if (wo->obstacles[i].isActive) {
            Obstacle *obs = &wo->obstacles[i];
            if (obs->isFloor) {
                float size = wo->size;
                obs->region.x = wo->offsetX + (float) i * size;
            } else {
                obs->region.x -= scaledDelta;
                obs->powerup.region.x -= scaledDelta;

                // cleanup when offscreen
                if (obs->region.x < -20 - wo->size) {
                    obs->isActive = false;
                    TraceLog(LOG_INFO, "Cleaned up block");
                }
            }
        }
    }

    // optical illusion
    float interval = wo->size * 2;
    if (wo->offsetX < -interval) {
        wo->offsetX += interval;
    }

    // spawn block every once in a while
    if (wo->spawnTimer < 0.0f) {
        float rng = (float) GetRandomValue(3, 30) * 0.1f;
        wo->spawnTimer += rng; // TODO random

        obstacle_place_block(wo);
    }
    wo->spawnTimer -= delta;
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
                // TODO this is bad
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
            float y = SCREEN_HEIGHT - (pos->y + 1) * wo->size;

            Color col = index % 2 == 0 ? wo->color : wo->colorAlt;
            Rectangle region = (Rectangle) {x, y, wo->size, wo->size};

            // initialize new obstacle
            obs->isActive = true;
            obs->isFloor = false;
            obs->hasPower = false;
            obs->region = region;
            obs->color = col;

            // initialize powerup on top
            float margin = 40;
            float height = 1.8f * region.height;
            float powerSize = wo->size - margin;
            obs->powerup.region = (Rectangle) {obs->region.x + powerSize / 2.0f,
                                               obs->region.y + powerSize / 2.0f - height, powerSize, powerSize};
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