#include "input.h"

#include "app.h"
#include "utils.h"
#include "output.h"
#include "terminal.h"

#include <stdlib.h>
#include <unistd.h>

#define CTRL_KEY(k) ((k) & 0x1f)

void Fed_Input_moveCursor(App *app, int key)
{
    switch(key)
    {
        case ARROW_LEFT:
            --app->cx;
            break;

        case ARROW_RIGHT:
            ++app->cx;
            break;

        case ARROW_UP:
            --app->cy;
            break;

        case ARROW_DOWN:
            ++app->cy;
            break;
    }

    if (app->rows.size == 0)
    {
        app->cx = 0;
        app->cy = 0;
        return;
    }

    CLAMP(app->cy, 0, (int)app->rows.size - 1);
    CLAMP(app->cx, 0, (int)app->rows.data[app->cy].size);
}

void Fed_Input_processKeyPress(App *app)
{
    int c = Fed_Terminal_readKey();

    switch(c)
    {
        case CTRL_KEY('q'):
            Fed_Output_clearScreen();
            exit(0);

        case HOME_KEY:
            app->cx = 0;
            break;

        case END_KEY:
            app->cx = (int)app->rows.data[app->cy].size;
            break;

        case PAGE_UP:
        case PAGE_DOWN: {
            for(int times = app->screenRows; times; times--)
                Fed_Input_moveCursor(app, c == PAGE_UP ? ARROW_UP : ARROW_DOWN);
        } break;

        case ARROW_UP:
        case ARROW_DOWN:
        case ARROW_LEFT:
        case ARROW_RIGHT:
            Fed_Input_moveCursor(app, c);
    }
}