#include "math.h"
#include <SDL2/SDL.h>

SDL_Color hexToColor(int hex){
    SDL_Color color;
    // 0xFFFFFFFF
    color.a = hex & 0xFF;
    color.r = (hex >> 24) & 0xFF;
    color.g = (hex >> 16) & 0xFF;
    color.b = (hex >> 8)  & 0xFF;
    return color;
}

SDL_Rect FRectToRect(SDL_FRect *rect){
    int x = (int)rect->x;
    int y = (int)rect->y;
    int w = (int)rect->w;
    int h = (int)rect->h;
    return (SDL_Rect) { x, y, w, h };
}
