#define _POSIX_C_SOURCE 200809L

#include "app.h"

int main(int argc, char **argv)
{
    const char *fileName = argc > 1 ? argv[1] : NULL;

    Fed_App_run(fileName);

    return 0;
}