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
bool bIsAlive = false;
float fOpacity = 255.0;

void player_init(void){
    SDL_Log("Created player");
    bIsAlive = true;
    fOpacity = 255.0;
    sCol = hexToColor(0x00ff00ff);
}

void player_update(float delta){
    if (bIsAlive)
    {
        fVelY += delta*GRAVITY;

        //SDL_Log("%f",rRegion.y);
        if (!player_move(0.0f,fVelY)){
            fVelY = 0.0f;
            bGrounded = true;
        }

        // check if touching obstacle "dying"
        if (obstacle_overlaps(&rRegion)){
            SDL_Log("dies");
            bIsAlive = false;
        }

        // spawn trail
        float y = rand()%((int)rRegion.h)+rRegion.y;
        SDL_FPoint pSpawn = {rRegion.x,y};
        SDL_FPoint pVel = randVelocity(30);
        pVel.x -= SPEED;

        particles_spawn(&pSpawn,&pVel, 1.0f, 8.0f,&sCol);
    }
    else // is dead lol 
    {
        // fade out
        Uint8 o = clamp((int)fOpacity,0,255);
        sCol = (SDL_Color) {sCol.r,sCol.g,sCol.b,o}; 
        fOpacity -= delta * 150.0f;


        // melt that gpu
        for (int i = 0; i < 100; i++){
            // spawn explosion 
            float y = rand()%((int)rRegion.h)+rRegion.y;
            float x = rand()%((int)rRegion.w)+rRegion.x;
            SDL_FPoint pSpawn = {x,y};
            SDL_FPoint pVel = randVelocity(50);
            pVel.x *= 10.0;
            pVel.y *= 10.0;
            particles_spawn(&pSpawn,&pVel, 1.0f, 8.0f,&sCol);
        }
    }
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
    if (obstacle_overlaps_floor(&rPredict, &fSnapY)){
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
    SDL_Log("%d %d %d %d",sCol.r,sCol.g,sCol.b,sCol.a);

    SDL_Rect rRect = FRectToRect(&rRegion);
    csc(SDL_RenderFillRect(app->renderer,&rRect));
}
