#include <SDL.h>
#include "main.h"
#include "defs.h"
#include "math.h"
#include "player.h"
#include "obstacle.h"

bool bIsRunning = true;
SDL_Color sBg = { NULL };

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

    // create the SDL2 window
    int nRenderFlags = SDL_RENDERER_ACCELERATED;
    int nWindowFlags = SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_RESIZABLE; 

    csc(SDL_Init(SDL_INIT_VIDEO));

    // initalize window
    App sApp;

    sApp.window = SDL_CreateWindow("SDL Endless Runner", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, nWindowFlags);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    // initialize renderer
	sApp.renderer = SDL_CreateRenderer(sApp.window, -1, nRenderFlags);

    SDL_Log("Created game of size %d by %d",WIDTH,HEIGHT);

    // init game components
    sBg = hexToColor(0x551122FF);
    obstacle_placeFloor();
    player_init();

    // main loop
    SDL_Event event;

    Uint64 nNow  = SDL_GetPerformanceCounter();
    Uint64 nPast = 0;
    float fDeltaTime = 0.0f;

    while(bIsRunning){

        nPast = nNow;
        nNow  = SDL_GetPerformanceCounter();

    	while (SDL_PollEvent(&event))
    	{
            handleInput(&event);
    	}

        fDeltaTime = (float)((nNow - nPast)*1.0f / (double)SDL_GetPerformanceFrequency());
        update(fDeltaTime);
        draw(csp(&sApp));

        SDL_Delay(1000 / FPS);
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
            SDL_Keycode sKey = event->key.keysym.sym;
            //SDL_Log("%s",SDL_GetKeyName(sKey));
            switch (sKey){
                case SDLK_SPACE:
                    SDL_Log("jump");
                    player_jump();
                    break;
            }
            break;
    	default:
    		break;
    }
}

void update(float delta){
    player_update(delta);
    obstacle_update(delta);
}

void draw(App *app){

    // draw background
    csc(SDL_SetRenderDrawColor(app->renderer,sBg.r,sBg.g,sBg.b,sBg.a));
    csc(SDL_RenderClear(app->renderer));

    player_draw(app);
    obstacle_draw(app);

    // show image
    SDL_RenderPresent(app->renderer);
}
