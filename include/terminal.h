#ifndef FED_TERMINAL_H
#define FED_TERMINAL_H

#include <stdbool.h>

#include <termios.h>

typedef enum EditorKey
{
    ARROW_LEFT = 1000,
    ARROW_RIGHT,
    ARROW_UP,
    ARROW_DOWN,
    DEL_KEY,
    HOME_KEY,
    END_KEY,
    PAGE_UP,
    PAGE_DOWN
}
EditorKey;

void Fed_Terminal_failure(const char *s);

void Fed_Terminal_enableRawMode(struct termios *original);
void Fed_Terminal_disableRawMode(struct termios *original);

int Fed_Terminal_readKey();
bool Fed_Terminal_getCursorPosition(int *rows, int *cols);
bool Fed_Terminal_getWindowSize(int *rows, int *cols);

#endif