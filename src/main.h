#ifndef MAIN_H 
#define MAIN_H
#include "defs.h"

#if defined(__linux__)
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_ttf.h>
#elif defined(_WIN64)
	#include <SDL.h>
	#include <SDL_ttf.h>
#endif

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
