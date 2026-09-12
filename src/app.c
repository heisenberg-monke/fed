#include "app.h"
#include "input.h"
#include "output.h"
#include "terminal.h"

void Fed_App_run()
{
    Fed_Terminal_enableRawMode();

    while(true)
    {
        Fed_Output_refreshScreen();
        Fed_Input_processKeyPress();
    }
        
}