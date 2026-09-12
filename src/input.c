#include "input.h"
#include "output.h"
#include "terminal.h"

#include <stdlib.h>

#define CTRL_KEY(k) ((k) & 0x1f)

void Fed_Input_processKeyPress()
{
    char c = Fed_Terminal_readKey();

    switch(c)
    {
        case CTRL_KEY('q'):
            Fed_Output_clearScreen();
            exit(0);
            break;
    }
}