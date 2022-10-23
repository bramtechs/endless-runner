//
// Created by bram on 10/23/22.
//

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "main.h"
#include "raylib.h"

#define BG_LAYER_COUNT 5
#define BG_BUILDING_COUNT 256

typedef struct {
    Rectangle region;
    Color color;
} Building;

typedef struct {
    float speed;
    int buildingCount;
    Building buildings[BG_BUILDING_COUNT];
} Layer;

typedef struct {
    int layerCount;
    float speed;

    Vector2 minSize;
    Vector2 maxSize;

    Layer layers[BG_LAYER_COUNT];
} Background;

Background background_init(void);

void background_update(Background *bg, float delta);

void background_draw(Background *bg);

#endif //BACKGROUND_H
