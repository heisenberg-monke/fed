#ifndef FED_INPUT_H
#define FED_INPUT_H

typedef struct App App;

void Fed_Input_moveCursor(App *app, int key);
void Fed_Input_processKeyPress(App *app);

#endif