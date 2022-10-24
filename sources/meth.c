//
// Created by bram on 10/22/22.
//
#include "meth.h"
#include "raylib.h"

Vector2 randVelocity(int power) {
    float x = (float) GetRandomValue(-power, power);
    float y = (float) GetRandomValue(-power, power);
    return (Vector2) {x, y};
}

Vector2 centerOfRectangle(Rectangle *rect) {
    float x = rect->x + rect->width * 0.5f;
    float y = rect->y + rect->height * 0.5f;
    return (Vector2) {x, y};
}

int clamp(int val, int min, int max){
    if (val < min){
        return min;
    }
    if (val > max){
        return max;
    }
    return val;
}
