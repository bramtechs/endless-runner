#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "defs.h"
#include <SDL2/SDL.h>
#include "main.h"

// Rectangles that stop the player

#define MAX_OBSTACLES 64
#define SIZE 64.0f 
#define FLOOR_SPEED 6.0f 
#define SPEED 500.0f 

typedef struct {
    bool bIsAlive;
    bool bIsFloor;
    bool bHasPower;
    SDL_FRect rRegion;
    SDL_FRect rPowerup;
    SDL_Color sColor;
    SDL_Color sPowerColor;
} Obstacle;

void obstacle_placeFloor(void);

bool obstacle_overlaps(const SDL_FRect *rect, float *snapY);
bool obstacle_overlaps_power(const SDL_FRect *rect);

void obstacle_update(float delta);
void obstacle_draw(App *app);
int obstacle_place(float x, float y, int index);
#endif // OBSTACLE_H
