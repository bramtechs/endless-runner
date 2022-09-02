#ifndef MATH_H
#define MATH_H

#include <SDL2/SDL.h>

SDL_Color hexToColor(int hex);
SDL_Rect FRectToRect(SDL_FRect *rect);
int randIntRange(int min, int max);

#endif // MATH_H
