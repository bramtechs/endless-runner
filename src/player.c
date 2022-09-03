#include "player.h"
#include "defs.h"
#include "main.h"
#include "math.h"
#include "obstacle.h"
#include "particles.h"

float fVelY = GRAVITY;
bool bGrounded = false;

SDL_FRect rRegion = { SIZE*4, HEIGHT/2.0f-SIZE*2.0f, SIZE, SIZE };
SDL_Color sCol = { NULL }; 
SDL_Color sTrailCol = { NULL }; 

void player_init(void){
    SDL_Log("Created player");
    sCol = hexToColor(0x22CC22FF);
}

void player_update(float delta){
    fVelY += delta*GRAVITY;

    //SDL_Log("%f",rRegion.y);
    if (!player_move(0.0f,fVelY)){
        fVelY = 0.0f;
        bGrounded = true;
    }

    // spawn trail
    float y = rand()%((int)rRegion.h)+rRegion.y;
    SDL_FPoint pSpawn = {rRegion.x,y};
    SDL_FPoint pVel = randVelocity(30);
    pVel.x -= SPEED;

    particles_spawn(&pSpawn,&pVel, 1.0f, 8.0f,&sCol);
}

// TODO make jump height not depend on framerate
void player_jump(void){
    bool bTouchesPowerup = obstacle_overlaps_power(&rRegion);
    if (!bGrounded && !bTouchesPowerup) return;
    fVelY = -JUMP_FORCE;
    player_move(0.0f,fVelY);
    bGrounded = false;
}

// TODO make stomp force not depend on framerate
void player_stomp(void){
    if (bGrounded) return;
    fVelY = STOMP_FORCE;
    player_move(0.0f,fVelY);
}

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
