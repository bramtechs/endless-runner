#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "main.h"

#define BG_LAYER_COUNT 5

#define BG_WIDTH_MAX 256
#define BG_WIDTH_MIN 80

#define BG_HEIGHT_MAX 700 
#define BG_HEIGHT_MIN 150

#define BG_MAX 256

#define BG_SPEED 32.0f

typedef struct {
    float fSpeed;
    int nCount;
    SDL_FRect aRects[BG_MAX];
    SDL_Color aColors[BG_MAX];
} BGLayer;

void background_init(void);
void background_initLayer(int index);

void background_update(float delta);
void background_draw(App *app);

#endif // BACKGROUND_H
