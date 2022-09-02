#ifndef PLAYER_H 
#define PLAYER_H
#include "defs.h"
#include "main.h"

#define SIZE 50
#define GRAVITY 20.0f
#define JUMP_FORCE 10.0f
#define STOMP_FORCE 15.0f

void player_init(void);
void player_update(float delta);
void player_draw(App *app);
void player_jump(void);
void player_stomp(void);
bool player_move(float x, float y);

#endif // PLAYER_H 
