#include "player.h"
#include "defs.h"
#include "main.h"
#include "math.h"
#include "obstacle.h"
#include <SDL2/SDL.h>

float fVelY = GRAVITY;
bool bGrounded = false;

SDL_FRect rRegion = { SIZE, HEIGHT/2.0f-SIZE*2.0f, SIZE, SIZE };
SDL_Color sCol = { NULL }; 

void player_init(void){
    SDL_Log("Created player");
    sCol = hexToColor(0x557722FF);
}

void player_update(float delta){
    fVelY += delta*GRAVITY;

    //SDL_Log("%f",rRegion.y);
    if (!player_move(0.0f,fVelY)){
        fVelY = 0.0f;
        bGrounded = true;
    }
}

void player_jump(void){
    bool bTouchesPowerup = obstacle_overlaps_power(&rRegion);
    if (!bGrounded && !bTouchesPowerup) return;
    fVelY = -JUMP_FORCE;
    player_move(0.0f,fVelY);
    bGrounded = false;
}

// TODO prevent odd bounce when landing
bool player_move(float x, float y){
    SDL_FRect rPredict = { rRegion.x + x, rRegion.y + y, rRegion.w, rRegion.h };

    // snap to y of obstacle if touching, else move normally
    float fSnapY = 0.0f;
    if (obstacle_overlaps(&rPredict, &fSnapY)){
        rRegion.y = fSnapY-rRegion.h; 
        return false;
    }else{
        rRegion.x += x;
        rRegion.y += y;
        return true;
    }
}

void player_draw(App *app){
    csp(app);

    csc(SDL_SetRenderDrawColor(app->renderer,sCol.r,sCol.g,sCol.b,sCol.a));

    SDL_Rect rRect = FRectToRect(&rRegion);
    csc(SDL_RenderFillRect(app->renderer,&rRect));
}
