#include "app.h"
#include "terminal.h"
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <unistd.h>

#define CTRL_KEY(k) ((k) & 0x1f)

void Fed_App_run()
{
    Fed_Terminal_enableRawMode();

    while(true)
    {
        char c = '\0';

        if(read(STDIN_FILENO, &c, 1) == -1 && errno != EAGAIN)
            Fed_Terminal_failure("Failed to read input");

        if(iscntrl(c))
            printf("%d\r\n", c);
        else
            printf("%d ('%c')\r\n", c, c);

        if(c == CTRL_KEY('q'))
            break;
    }
}