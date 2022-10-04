#include "main.h"
#include "defs.h"
#include "math.h"
#include "player.h"
#include "obstacle.h"
#include "background.h"
#include "particles.h"
#include <time.h>
#include <stdlib.h>

bool bIsRunning = true;
SDL_Color sBg = { NULL };
int nFrameNumber = 0;

bool bHoldingJump = false;
bool bHoldingStomp = false;

// set 1 for benchmark purposes
// and checking memory leaks
#define FAST_MODE 0 

// check sdl code if not 0
bool csc(int code){ 
    if (code != 0){
        SDL_LogError(code,"SDL function failed %d -> %s",code,SDL_GetError());
        exit(1);
        return false;
    }
    return true;
}

// check sdl pointer
void* csp(void* ptr){
    if (ptr == NULL){
        SDL_LogError(0,"SDL didn't return pointer");
        exit(1);
        return NULL;
    }
    return ptr;
}

int main(void){

    // rng
    srand(time(NULL));   // Initialization, should only be called once.

    // create the SDL2 window
    int nRenderFlags = SDL_RENDERER_ACCELERATED;
    int nWindowFlags = SDL_WINDOW_ALWAYS_ON_TOP; 

    csc(SDL_Init(SDL_INIT_VIDEO));

    // initalize window
    App sApp;

    sApp.window = SDL_CreateWindow("SDL Endless Runner", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, nWindowFlags);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    // initialize renderer
	sApp.renderer = SDL_CreateRenderer(sApp.window, -1, nRenderFlags);
    SDL_SetRenderDrawBlendMode(sApp.renderer,SDL_BLENDMODE_BLEND);

    SDL_Log("Created game of size %d by %d",WIDTH,HEIGHT);

    // init game components
    sBg = hexToColor(0xd4e4ff);
    obstacle_init();
    player_init();
    background_init();

    // main loop
    SDL_Event event;

    Uint64 nNow  = SDL_GetPerformanceCounter();
    Uint64 nPast = 0;
    float fDeltaTime = 0.0f;
    float fFPS = 0.0f;

    while(bIsRunning){

        nPast = nNow;
        nNow  = SDL_GetPerformanceCounter();

    	while (SDL_PollEvent(&event))
    	{
            handleInput(&event);
    	}

#if (FAST_MODE == 1)
        fDeltaTime = 0.1f;
#else
        fDeltaTime = (float)((nNow - nPast)*1.0f / (double)SDL_GetPerformanceFrequency());
#endif
        fFPS = 1.0f / fDeltaTime;
        update(fDeltaTime);
        draw(csp(&sApp));

        if (nFrameNumber % MAX_FPS*5 == 0){
            SDL_Log("FPS %f",fFPS);
        }
        
        nFrameNumber++;
        SDL_Delay(1000 / MAX_FPS);
    }

    SDL_Log("Shutting down...");

    return 0;
}

void handleInput(SDL_Event *event){
    switch (event->type)
    {
    	case SDL_QUIT:
            bIsRunning = false;
    		exit(0);
    		break;
        case SDL_KEYDOWN:
            //SDL_Log("%s",SDL_GetKeyName(sKey));
            switch (event->key.keysym.sym){
                case SDLK_SPACE:
                    bHoldingJump = true;
                    break;
                case SDLK_TAB:
                    bHoldingStomp = true;
                    break;
            }
            break;
        case SDL_KEYUP:
            switch (event->key.keysym.sym){
                case SDLK_SPACE:
                    bHoldingJump = false;
                    break;
                case SDLK_TAB:
                    bHoldingStomp = false;
                    break;
            }
            break;
    }
}

void update(float delta){
    if (bHoldingJump){
        player_jump();
    }
    if (bHoldingStomp){
        player_stomp();
    }

    background_update(delta);
    particles_update(delta);
    player_update(delta);
    obstacle_update(delta);
}

void draw(App *app){

    // draw background
    csc(SDL_SetRenderDrawColor(app->renderer,sBg.r,sBg.g,sBg.b,sBg.a));
    csc(SDL_RenderClear(app->renderer));

    background_draw(app);
    particles_draw(app);
    player_draw(app);
    obstacle_draw(app);

    // show image
    SDL_RenderPresent(app->renderer);
}
