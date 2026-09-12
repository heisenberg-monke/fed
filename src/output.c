#include "output.h"

#include <unistd.h>

void Fed_Output_drawRows()
{
    for(int y = 0; y < 24; ++y)
        write(STDOUT_FILENO, "~\r\n", 3);
}

void Fed_Output_clearScreen()
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}

void Fed_Output_refreshScreen() 
{
    Fed_Output_clearScreen();
}