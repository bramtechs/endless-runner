//
// Created by bram on 10/22/22.
//
#include "raylib.h"
#include "meth.h"
#include "main.h"
#include "player.h"
#include "background.h"
#include "particle.h"

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Endless Runner");
    SetTargetFPS(60);

    RenderTexture2D target = LoadRenderTexture(SCREEN_WIDTH, SCREEN_HEIGHT);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

    Color bgColor = GetColor(0XD4E4FF);

    Background bg = background_init();
    ParticleWorld pw = particle_init();
    ObstacleWorld world = obstacle_init();
    Player player = player_init(&world,&pw);

    while (!WindowShouldClose()) {
        // update
        float delta = GetFrameTime();

        background_update(&bg, delta);
        player_update(&player, delta);
        obstacle_update(&world, delta);
        particle_update(&pw, delta);

        BeginTextureMode(target);

        ClearBackground(bgColor);

        background_draw(&bg);
        obstacle_draw(&world);
        player_draw(&player);
        particle_draw(&pw);

        EndTextureMode();

        BeginDrawing();

        ClearBackground(BLACK);

        float scale = MIN((float) GetScreenWidth() / SCREEN_WIDTH, (float) GetScreenHeight() / SCREEN_HEIGHT);

        // Draw render texture to screen, properly scaled
        DrawTexturePro(target.texture,
                       (Rectangle) {0.0f, 0.0f, (float) target.texture.width, (float) -target.texture.height},
                       (Rectangle) {((float) GetScreenWidth() - ((float) SCREEN_WIDTH * scale)) * 0.5f,
                                    ((float) GetScreenHeight() - ((float) SCREEN_HEIGHT * scale)) * 0.5f,
                                    (float) SCREEN_WIDTH * scale, (float) SCREEN_HEIGHT * scale}, (Vector2) {0, 0},
                       0.0f, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}