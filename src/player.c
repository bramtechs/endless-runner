#include "player.h"
#include "defs.h"
#include "main.h"
#include "math.h"
#include "obstacle.h"
#include <SDL2/SDL.h>

float fVelY = GRAVITY;

SDL_Rect rRegion = { SIZE, HEIGHT/2-SIZE*2, SIZE, SIZE };
SDL_Color sCol = { NULL }; 

void player_init(void){
    SDL_Log("Created player");
    sCol = hexToColor(0x557722FF);
}

void player_update(float delta){
    fVelY += delta*GRAVITY;

    if (!player_move(0.0f,fVelY)){
        fVelY = 0.0f;
    }
}

void player_jump(void){

}

bool player_move(float x, float y){
    int nAddX = (int)x;
    int nAddY = (int)y;
    SDL_Rect rPredict = { rRegion.x+nAddX, rRegion.y + nAddY, rRegion.w, rRegion.h };

    // don't move if touching obstacle 
    if (obstacle_overlaps(&rPredict)){
        return false;
    }else{
        rRegion.x += nAddX;
        rRegion.y += nAddY;
        return true;
    }
}

void player_draw(App *app){
    csp(app);

    csc(SDL_SetRenderDrawColor(app->renderer,sCol.r,sCol.g,sCol.b,sCol.a));
    csc(SDL_RenderFillRect(app->renderer,&rRegion));
}
