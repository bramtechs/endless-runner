#include "player.h"
#include "defs.h"
#include "main.h"
#include "math.h"
#include <SDL.h>

float fVelY = GRAVITY;

SDL_Rect rRegion = { SIZE, HEIGHT/2-SIZE*2, SIZE, SIZE };
SDL_Color sCol = { NULL }; 

void player_init(void){
    SDL_Log("Created player");
    sCol = hexToColor(0x557722FF);
}

void player_update(float delta){
    fVelY += delta*GRAVITY;

    rRegion.y += (int)fVelY;
}

void player_draw(App *app){
    csp(app);

    csc(SDL_SetRenderDrawColor(app->renderer,sCol.r,sCol.g,sCol.b,sCol.a));
    csc(SDL_RenderFillRect(app->renderer,&rRegion));
}
