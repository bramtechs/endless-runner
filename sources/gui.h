//
// Created by bram on 10/25/22.
//

#ifndef GUI_H
#define GUI_H

#include "raylib.h"
#include "main.h"

typedef struct {
    Font font;
    float timer;
    bool isCounting;
} GUI;

GUI gui_init(void);

void gui_stop(GUI *gui);

void gui_update(GUI *gui, float delta);

void gui_draw(GUI *gui);

void gui_dispose(GUI *gui);

#endif //GUI_H
