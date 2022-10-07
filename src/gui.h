#ifndef GUI_H
#define GUI_H

#include "main.h"

void gui_init(App* app);
void gui_dispose(void);
void gui_stop(void);
void gui_update(float delta);
void gui_draw(App* app);

#endif // GUI_H
