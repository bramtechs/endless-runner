#pragma once

// main.c
#define WIDTH 1280 
#define HEIGHT 704
#define MAX_FPS 60

#define bool SDL_bool 
#define byte char
#define true SDL_TRUE 
#define false SDL_FALSE 

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

// platform.c
void PLAT_LogError(char[] buffer);
void PLAT_LogInfo(char[] buffer);
void PLAT_Init(void);

// math.h
SDL_Color hexToColor(int hex);
SDL_Rect FRectToRect(SDL_FRect *rect);
int randIntRange(int min, int max);
SDL_FPoint randVelocity(int power);
SDL_FPoint centerOfFRect(SDL_FRect *rect);

// background.c
#define bg_layer_count 5

#define bg_width_max 256
#define bg_width_min 80

#define bg_height_max 700 
#define bg_height_min 150

#define bg_max 256

#define bg_speed 32.0f

#define size 50
#define GRAVITY 20.0f
#define JUMP_FORCE 10.0f
#define STOMP_FORCE 15.0f

typedef struct {
    float fSpeed;
    int nCount;
    SDL_FRect aRects[BG_MAX];
    SDL_Color aColors[BG_MAX];
} BGLayer;

void background_init();
void background_initLayer(int index);

void background_update(float delta);
void background_draw(App *app);

// player.c
void player_init(void);
void player_update(float delta);
void player_draw(App *app);
void player_jump(void);
void player_stomp(void);
bool player_move(float x, float y);

// obstacle.c
#define MAX_OBSTACLES 64
#define SIZE 64.0f 
#define FLOOR_SPEED 6.0f 
#define SPEED 500.0f 

typedef struct {
    bool bIsAlive;
    bool bIsFloor;
    bool bHasPower;
    SDL_FRect rRegion;
    SDL_FRect rPowerup;
    SDL_Color sColor;
    SDL_Color sPowerColor;
} Obstacle;

void obstacle_init(void);

bool obstacle_overlaps(const SDL_FRect *rect, float *snapY);
bool obstacle_overlaps_power(const SDL_FRect *rect);

void obstacle_update(float delta);
void obstacle_draw(App *app);
int obstacle_place(float x, float y, int index);

// particles.c
#define PARTICLES_H
#define MAX_PARTICLES 256

typedef struct {
    bool bIsAlive;
    float fLifetime;
    SDL_FPoint v2Velocity; 
    SDL_FRect rRegion;
    SDL_Color sColor;
} Particle;

int particles_spawn(SDL_FPoint *pos, SDL_FPoint *vel,
        float lifetime, float size, SDL_Color *col);

void particles_draw(App *app);
void particles_update(float delta);