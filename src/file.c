#include "file.h"

#include "app.h"
#include "terminal.h"
#include "utils.h"

#include <stdio.h>

void Fed_File_open(App *app, const char *fileName)
{
    FILE *file = fopen(fileName, "r");

    if(!file)
        Fed_Terminal_failure("Failed to open file");

    int c;
    String line = {0};

    while((c = fgetc(file)) != EOF)
    {
        if(c == '\r')
            continue;
        
        if(c == '\n')
        {
            VEC_PUSH(&app->rows, line);
            line = (String){0};
        }

        else 
            STR_PUSH(&line, (char)c);
    }

    if(line.size > 0)
        VEC_PUSH(&app->rows, line);

    fclose(file);
}