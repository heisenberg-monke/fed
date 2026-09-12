#ifndef FED_TERMINAL_H
#define FED_TERMINAL_H

#include <stdbool.h>

#include <termios.h>

void Fed_Terminal_failure(const char *s);

void Fed_Terminal_enableRawMode(struct termios *original);
void Fed_Terminal_disableRawMode(struct termios *original);

char Fed_Terminal_readKey();
bool Fed_Terminal_getCursorPosition(int *rows, int *cols);
bool Fed_Terminal_getWindowSize(int *rows, int *cols);

#endif