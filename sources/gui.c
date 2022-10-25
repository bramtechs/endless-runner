//
// Created by bram on 10/25/22.
//

#include "gui.h"

GUI gui_init(void) {
    Font font = LoadFont("assets/font.ttf");

    return (GUI) {
            .font = font,
            .timer = 0.0f,
            .isCounting = true,
    };
}

void gui_stop(GUI *gui) {
    gui->isCounting = false;
}

void gui_update(GUI *gui, float delta) {
    if (gui->isCounting){
        gui->timer += delta*10.0f;
    }
}

void gui_draw(GUI *gui) {
    int score = (int) gui->timer;
    const char *text = TextFormat("%dm", score);
    float fontSize = 72;
    float spacing = 5.0f;
    Vector2 pos = (Vector2) {
            (SCREEN_WIDTH - MeasureTextEx(gui->font, text, fontSize, spacing).x) / 2.0f ,
            SCREEN_HEIGHT / 3.0f
    };
    DrawTextEx(gui->font, text, pos, fontSize, spacing, WHITE);
}

void gui_dispose(GUI *gui){
    UnloadFont(gui->font);
}