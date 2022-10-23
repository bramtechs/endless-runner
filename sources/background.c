//
// Created by bram on 10/23/22.
//

#include <assert.h>
#include "background.h"

void background_init_layer(Background *bg, int index) {
    Layer *layer = &bg->layers[index];
    layer->speed = bg->speed * (float) (index+1) * 5.0f;

    float percent = (float)(BG_LAYER_COUNT - index) / (float) BG_LAYER_COUNT;

    float penX = 0;
    int column = 0;

    while (penX < SCREEN_WIDTH) {
        assert(column < BG_BUILDING_COUNT);

        float width = (float) GetRandomValue((int) bg->minSize.x, (int) bg->maxSize.x);
        float height = (float) GetRandomValue((int) bg->minSize.y, (int) bg->maxSize.y)*percent;

        // generate building
        Building *building = &layer->buildings[column];
        building->region = (Rectangle) {
                .x = penX,
                .y = SCREEN_HEIGHT - height,
                .width = width,
                .height = height,
        };

        // set color
        Color *color = &building->color;
        color->r = (unsigned char) GetRandomValue(80, 180);
        color->g = (unsigned char) GetRandomValue(80, 180);
        color->b = (unsigned char) GetRandomValue(80, 180);
        color->a = (unsigned char) 255;

        penX += width;
        column++;
    }

    layer->buildingCount = column;
}

Background background_init(void) {
    Background bg = (Background) {
            .layerCount = 5,
            .speed = 32.0f,

            .minSize = (Vector2) {80.0f, 150.0f},
            .maxSize = (Vector2) {256.0f, 700.0f},
    };

    // spawn layers
    for (int i = 0; i < BG_LAYER_COUNT; i++) {
        background_init_layer(&bg, i);
    }

    return bg;
}

void background_update(Background *bg, float delta) {
    // update each layer
    for (int i = 0; i < BG_LAYER_COUNT; i++){
        Layer *layer = &bg->layers[i];

        // update each building
        for (int j = 0; j < layer->buildingCount; j++){
            Rectangle *region = &layer->buildings[j].region;
            region->x -= layer->speed*delta;

            // wrap bulidings around
            if (region->x < -region->width){
                region->x = SCREEN_WIDTH;
            }
        }
    }
}

void background_draw(Background *bg) {
    // draw each layer
    for (int i = 0; i < BG_LAYER_COUNT; i++){
        Layer *layer = &bg->layers[i];

        // draw each building
        for (int j = 0; j < layer->buildingCount; j++) {
            Building *building = &layer->buildings[j];
            DrawRectangleRec(building->region,building->color);
        }
    }
}