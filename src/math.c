#include "endless.h"

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

int randIntRange(int min, int max){
    return rand()%(max-min)+min;
}

SDL_FPoint randVelocity(int power){
    float x = rand()%power*2.f-power; 
    float y = rand()%power*2.f-power;
    return (SDL_FPoint) { x , y };
}

SDL_FPoint centerOfFRect(SDL_FRect *rect){
    float x = rect->x+rect->w*0.5f;
    float y = rect->y+rect->h*0.5f;
    return (SDL_FPoint) { x,y };
}
