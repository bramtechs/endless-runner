//
// Created by bram on 10/22/22.
//

#include "player.h"
#include "stdbool.h"
#include "main.h"
#include "obstacle.h"

Player player_init(ObstacleWorld *world) {
    TraceLog(LOG_INFO, "Initializing player...");
    float size = 50.0f;
    return (Player) {
            .gravity = 20.0f,
            .jumpForce = 10.0f,
            .stompForce = 15.0f,
            .region = (Rectangle) {size * 4.0f, SCREEN_HEIGHT * 0.5f - SIZE * 2.0f, size, size},
            .vel = (Vector2) {0},
            .isAlive = true,
            .opacity = 255.0f,
            .color = GetColor(0x00ff00ff),

            .world = world,
    };
}

void player_update_alive(Player *pl, float delta) {
    pl->vel.y += delta * pl->gravity;

    if (!player_grounded(pl)) {
        // touched floor
        pl->region.y = pl->region.height;
        pl->vel.y = 0.0f;
    } else {
        // freely move
        Vector2 downwards = (Vector2) {0.0f, pl->vel.y};
        player_move(pl, &downwards);
    }

    //if (obstacle_overlaps(&pl->region)){
    //    pl->isAlive = false;
    //}
}

void player_update_dead(Player *pl, float delta) {
     // TODO
}

void player_jump(Player *pl) {
    //ObstacleWorld world = pl.
    if (player_grounded(pl) || obstacle_overlaps(pl->world,&pl->region,FLOOR)){
        pl->vel.y = -pl->jumpForce;
        Vector2 offset = (Vector2) {0.0f, pl->vel.y};
        player_move(pl,&offset);
        // TODO might break grounded
    }
}

void player_stomp(Player *pl) {
    if (player_grounded(pl)) {
        pl->vel.y = pl->stompForce;
        Vector2 offset = (Vector2) {0.0f, pl->vel.y};
        player_move(pl,&offset);
    }
}

void player_update(Player *pl, float delta) {
    // check key inputs
    if (IsKeyPressed(KEY_SPACE)){
        player_jump(pl);
    }
    if (IsKeyPressed(KEY_TAB)){
        player_stomp(pl);
    }

    if (pl->isAlive) {
        player_update_alive(pl, delta);
    } else {
        player_update_dead(pl, delta);
    }
}

void player_draw(Player *pl) {
    DrawRectangleRec(pl->region,pl->color);
}

void player_move(Player *pl, Vector2 *offset) {
    pl->region.x += offset->x;
    pl->region.y += offset->y;
}

bool player_grounded(Player *pl){
    Vector2 offset = (Vector2) {0.0f, pl->vel.y};
    Rectangle predict = {pl->region.x + offset.x, pl->region.y + offset.y, pl->region.width, pl->region.height};
    return !obstacle_overlaps(pl->world, &predict, FLOOR);
}

