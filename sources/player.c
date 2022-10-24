//
// Created by bram on 10/22/22.
//

#include "player.h"
#include "stdbool.h"
#include "main.h"
#include "meth.h"
#include "obstacle.h"
#include "particle.h"

Player player_init(ObstacleWorld *world, ParticleWorld *particles) {
    TraceLog(LOG_INFO, "Initializing player...");
    float size = 50.0f;
    return (Player) {
            .gravity = 20.0f,
            .jumpForce = 10.0f,
            .stompForce = 15.0f,
            .opacity = 255.0f,
            .region = (Rectangle) {size * 4.0f, SCREEN_HEIGHT * 0.5f - SIZE * 2.0f, size, size},
            .vel = (Vector2) {0},
            .color = GetColor(0x00ff00ff),
            .isAlive = true,
            .isGrounded = false,

            .world = world,
            .particles = particles,
    };
}

void player_update_alive(Player *pl, float delta) {
    pl->vel.y += delta * pl->gravity;

    Vector2 downwards = (Vector2) {0.0f, pl->vel.y};
    if (!player_move(pl, &downwards)) {
        pl->vel.y = 0.0f;
        pl->isGrounded = true;
    }

    // check death
    if (obstacle_overlaps(pl->world, &pl->region, BLOCK)) {
        pl->isAlive = false;
    }

    // spawn trail of particles
    float y = (float) GetRandomValue((int) pl->region.y, (int) (pl->region.y + pl->region.height));
    Vector2 spawn = {pl->region.x + 15, y};
    Vector2 vel = randVelocity(30);
    vel.x -= pl->world->speed;

    particle_spawn(pl->particles, &spawn, &vel, 1.0f, 8.0f, &pl->color);
}

void player_update_dead(Player *pl, float delta) {
    // TODO
}

void player_jump(Player *pl) {
    //ObstacleWorld world = pl.
    if (pl->isGrounded) {
        pl->vel.y = -pl->jumpForce;
        Vector2 offset = (Vector2) {0.0f, pl->vel.y};
        player_move(pl, &offset);
        pl->isGrounded = false;
    }
}

void player_stomp(Player *pl) {
    if (!pl->isGrounded) {
        pl->vel.y = pl->stompForce;
        Vector2 offset = (Vector2) {0.0f, pl->vel.y};
        player_move(pl, &offset);
    }
}

void player_update(Player *pl, float delta) {
    // check key inputs
    if (IsKeyDown(KEY_SPACE)) {
        player_jump(pl);
    }
    if (IsKeyPressed(KEY_TAB)) {
        player_stomp(pl);
    }

    if (pl->isAlive) {
        player_update_alive(pl, delta);
    } else {
        player_update_dead(pl, delta);
    }
}

void player_draw(Player *pl) {
    if (pl->isAlive) {
        DrawRectangleRec(pl->region, pl->color);
    }
}

bool player_move(Player *pl, Vector2 *offset) {
    Rectangle predict = {pl->region.x + offset->x, pl->region.y + offset->y, pl->region.width, pl->region.height};

    if (obstacle_overlaps(pl->world, &predict, FLOOR)) {
        return false;
    } else {
        pl->region.x += offset->x;
        pl->region.y += offset->y;
        return true;
    }
}