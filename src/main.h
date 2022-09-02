#ifndef MAIN_H 
#define MAIN_H
#include "defs.h"
#include <SDL2/SDL.h>

extern bool bIsRunning;

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

bool csc(int code);
void* csp(void* ptr);

int main(void);
void handleInput(SDL_Event *event);
void update(float delta);
void draw(App *app);

#endif // MAIN_H
