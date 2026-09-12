#include "app.h"
#include "input.h"
#include "output.h"
#include "terminal.h"

#include <stdlib.h>

static App g_app;

void Fed_App_Init()
{
    if(!Fed_Terminal_getWindowSize(&g_app.screenRows, &g_app.screenCols))
        Fed_Terminal_failure("Failed to get window size.");

    atexit(Fed_App_shutdown);
}

void Fed_App_shutdown()
{
    Fed_Terminal_disableRawMode(&g_app.original);
}

void Fed_App_run()
{
    Fed_Terminal_enableRawMode(&g_app.original);
    Fed_App_Init();

    while(true)
    {
        Fed_Output_refreshScreen(&g_app);
        Fed_Input_processKeyPress();
    }
}