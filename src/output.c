#include "app.h"
#include "output.h"

#include <unistd.h>

void Fed_Output_drawRows(App *app)
{
    for(int y = 0; y < app->screenRows; ++y)
    {
        write(STDOUT_FILENO, "~", 1);

        if(y < app->screenRows - 1)
            write(STDOUT_FILENO, "\r\n", 2);
    }
        
}

void Fed_Output_clearScreen()
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}

void Fed_Output_refreshScreen(App *app) 
{
    Fed_Output_clearScreen();
    Fed_Output_drawRows(app);

    write(STDOUT_FILENO, "\x1b[H", 3);
}