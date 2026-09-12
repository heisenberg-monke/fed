#include "input.h"

#include "app.h"
#include "utils.h"
#include "output.h"
#include "terminal.h"

#include <stdlib.h>
#include <unistd.h>

#define CTRL_KEY(k) ((k) & 0x1f)

void Fed_Input_moveCursor(App *app, char key)
{
    switch(key)
    {
        case 'a':
            --app->cx;
            break;

        case 'd':
            ++app->cx;
            break;

        case 'w':
            --app->cy;
            break;

        case 's':
            ++app->cy;
            break;
    }

    CLAMP(app->cx, 0, app->screenCols - 1);
    CLAMP(app->cy, 0, app->screenRows - 1);
}

void Fed_Input_processKeyPress(App *app)
{
    char c = Fed_Terminal_readKey();

    switch(c)
    {
        case CTRL_KEY('q'):
            Fed_Output_clearScreen();
            exit(0);

        case 'w':
        case 's':
        case 'a':
        case 'd':
            Fed_Input_moveCursor(app, c);
    }
}