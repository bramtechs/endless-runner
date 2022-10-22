#ifndef MATH_H
#define MATH_H

SDL_Color hexToColor(int hex);
SDL_Rect FRectToRect(SDL_FRect *rect);
int randIntRange(int min, int max);
SDL_FPoint randVelocity(int power);
SDL_FPoint centerOfFRect(SDL_FRect *rect);
int clamp(int val, int min, int max);

#endif // MATH_H
