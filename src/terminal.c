#include "terminal.h"
#include "output.h"

#include <stdlib.h>
#include <stdio.h>

#include <errno.h>
#include <unistd.h>
#include <termios.h>

struct termios g_original;

void Fed_Terminal_failure(const char *s)
{
    Fed_Output_clearScreen();
    fprintf(stderr, "[ERROR] ");
    perror(s);
    exit(EXIT_FAILURE);
}

void Fed_Terminal_enableRawMode()
{
    if(tcgetattr(STDIN_FILENO, &g_original) == -1)
        Fed_Terminal_failure("Failed to get terminal attributes");
    atexit(Fed_Terminal_disableRawMode);

    struct termios raw = g_original;
    
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= ~(CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        Fed_Terminal_failure("Failed to set terminal attributes");
}

void Fed_Terminal_disableRawMode() 
{
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &g_original) == -1)
        Fed_Terminal_failure("Failed to set disable raw mode");
}

char Fed_Terminal_readKey()
{
    int nRead;
    char c;

    while((nRead = read(STDIN_FILENO, &c, 1)) != 1)
    {
        if(nRead == -1 && errno != EAGAIN)
            Fed_Terminal_failure("Failed to read input");
    }

    return c;
}