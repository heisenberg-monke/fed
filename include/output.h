#ifndef FED_OUTPUT_H
#define FED_OUTPUT_H

typedef struct App App;
typedef struct String String;

void Fed_Output_drawRows(App *app, String *str);
void Fed_Output_clearScreen();
void Fed_Output_refreshScreen(App *app);

#endif