#ifndef PLAYER_H 
#define PLAYER_H
#include "defs.h"
#include "main.h"

#define SIZE 50
#define GRAVITY 5.0f

void player_init(void);
void player_update(float delta);
void player_draw(App *app);

#endif // PLAYER_H 
