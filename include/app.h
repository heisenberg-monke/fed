#ifndef FED_APP_H
#define FED_APP_H

#include <termios.h>

typedef struct App
{
    int cx;
    int cy;
    int screenRows;
    int screenCols;
    struct termios original;
}
App;

void Fed_App_Init();
void Fed_App_shutdown();

void Fed_App_run();

#endif