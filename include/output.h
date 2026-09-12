#ifndef FED_OUTPUT_H
#define FED_OUTPUT_H

typedef struct App App;

void Fed_Output_drawRows(App *app);
void Fed_Output_clearScreen();
void Fed_Output_refreshScreen(App *app);

#endif