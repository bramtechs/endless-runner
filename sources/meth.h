//
// Created by bram on 10/22/22.
//

// it's called meth.h to not get confused with the standard <math.h>

#ifndef METH_H
#define METH_H

#include "raylib.h"

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

Vector2 randVelocity(int power);
Vector2 centerOfRectangle(Rectangle *rect);

int clamp(int val, int min, int max);

#endif //METH_H
