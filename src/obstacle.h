#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "defs.h"
#include <SDL.h>
#include "main.h"

// Rectangles that stop the player

#define MAX_OBSTACLES 64
#define SIZE 64 
#define SPEED 6 

typedef struct {
    bool bIsAlive;
    bool bIsFloor;
    SDL_Rect rRegion;
    SDL_Color sColor;
} Obstacle;

void obstacle_placeFloor(void);

bool obstacle_overlaps(const SDL_Rect *rect);

void obstacle_update(float delta);
void obstacle_draw(App *app);

#endif // OBSTACLE_H
