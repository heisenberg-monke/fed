#include "app.h"
#include "output.h"

#define FED_UTILS_C
#include "utils.h"

#include <unistd.h>

void Fed_Output_drawRows(App *app, String *str)
{
    for(int y = 0; y < app->screenRows; ++y)
    {
        if(y == app->screenRows / 3)
        {
            const char *welcome = "WELCOME TO FED, NIGGAS. WE FEDPOST HERE.";
            size_t welcomeLen = strlen(welcome);

            if(welcomeLen > (size_t) app->screenCols)
                welcomeLen = app->screenCols;

            int padding = (app->screenCols - welcomeLen) / 2;

            if(padding)
            {
                STR_PUSH(str, '~');
                --padding;
            }

            while(padding--)
                STR_PUSH(str, ' ');

            STR_PUSH_BUF(str, welcome, welcomeLen);
        }
        else
            STR_PUSH(str, '~');

        STR_PUSH_CSTR(str, "\x1b[K");
        if(y < app->screenRows - 1)
            STR_PUSH_CSTR(str, "\r\n");
    }
}

void Fed_Output_clearScreen()
{
    write(STDOUT_FILENO, "\x1b[2J", 4);
    write(STDOUT_FILENO, "\x1b[H", 3);
}

void Fed_Output_refreshScreen(App *app) 
{
    String str = {0};

    STR_PUSH_CSTR(&str, "\x1b[?25l");
    STR_PUSH_CSTR(&str, "\x1b[H");

    Fed_Output_drawRows(app, &str);

    STR_PUSH_F(&str, "\x1b[%d;%dH", app->cy + 1, app->cx + 1);
    STR_PUSH_CSTR(&str, "\x1b[?25h");
    STR_PUSH(&str, '\0');

    write(STDOUT_FILENO, str.data, str.size);

    free(str.data);
}