#ifndef FED_APP_H
#define FED_APP_H

#include <termios.h>

#include <stddef.h>

typedef struct String String;

typedef struct Rows
{
    String *data;
    size_t size;
    size_t capacity;
}
Rows;

typedef struct App
{
    int cx;
    int cy;
    int rowOff;
    int colOff;
    int screenRows;
    int screenCols;
    Rows rows;
    struct termios original;
}
App;

void Fed_App_Init();
void Fed_App_shutdown();

void Fed_App_run(const char *fileName);

#endif