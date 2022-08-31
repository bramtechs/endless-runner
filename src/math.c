#include "math.h"
#include <SDL.h>

SDL_Color hexToColor(int hex){
    SDL_Color color;
    // 0xFFFFFFFF
    color.a = hex & 0xFF;
    color.r = (hex >> 24) & 0xFF;
    color.g = (hex >> 16) & 0xFF;
    color.b = (hex >> 8)  & 0xFF;
    return color;
}
