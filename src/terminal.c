#include "terminal.h"

#include "output.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include <errno.h>
#include <unistd.h>
#include <termios.h>

#include <sys/ioctl.h>

void Fed_Terminal_failure(const char *s)
{
    Fed_Output_clearScreen();
    fprintf(stderr, "[ERROR] ");
    perror(s);
    exit(EXIT_FAILURE);
}

void Fed_Terminal_enableRawMode(struct termios *original)
{
    if(tcgetattr(STDIN_FILENO, original) == -1)
        Fed_Terminal_failure("Failed to get terminal attributes");

    struct termios raw = *original;
    
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= ~(CS8);
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1)
        Fed_Terminal_failure("Failed to set terminal attributes");
}

void Fed_Terminal_disableRawMode(struct termios *original) 
{
    if(tcsetattr(STDIN_FILENO, TCSAFLUSH, original) == -1)
        Fed_Terminal_failure("Failed to set disable raw mode");
}

int Fed_Terminal_readKey()
{
    int nRead;
    char c;

    while((nRead = read(STDIN_FILENO, &c, 1)) != 1)
    {
        if(nRead == -1 && errno != EAGAIN)
            Fed_Terminal_failure("Failed to read input");
    }

    if(c == '\x1b')
    {
        char seq[3];

        if(read(STDIN_FILENO, &seq[0], 1) != 1 || read(STDIN_FILENO, &seq[1], 1) != 1)
            return '\x1b';

        if(seq[0] == '[')
        {
            if('0' <= seq[1]  && seq[1] <= '9')
            {
                if(read(STDIN_FILENO, &seq[2], 1) != 1)
                    return '\x1b';

                if(seq[2] == '~')
                {
                    switch(seq[1])
                    {
                        case '1': return HOME_KEY;
                        case '4': return END_KEY;
                        case '5': return PAGE_UP;
                        case '6': return PAGE_DOWN;
                        case '7': return HOME_KEY;
                        case '8': return END_KEY;
                    }
                }
            }

            else  {
                switch(seq[1])
                {
                    case 'A': return ARROW_UP;
                    case 'B': return ARROW_DOWN;
                    case 'C': return ARROW_RIGHT;
                    case 'D': return ARROW_LEFT;
                    case 'H': return HOME_KEY;
                    case 'F': return END_KEY;
                }
            }
        }

        else if(seq[0] == 'O')
        {
            switch(seq[1])
            {
                case 'H': return HOME_KEY;
                case 'F': return END_KEY;
            }
        }

        return '\x1b';
    }

    return c;
}

bool Fed_Terminal_getCursorPosition(int *rows, int *cols)
{
    char buf[32];
    uint32_t i = 0;

    if(write(STDOUT_FILENO, "\x1b[6n", 4) != 4)
        return false;

    while(i < sizeof(buf) - 1)
    {
        if(read(STDIN_FILENO, &buf[i], 1) != 1)
            break;

        if(buf[i] == 'R')
            break;

        ++i;
    }

    buf[i] = '\0';

    if(buf[0] != '\x1b' || buf[1] != '[')
        return false;

    if(sscanf(&buf[2], "%d;%d", rows, cols) != 2)
        return false;

    return true;
}

bool Fed_Terminal_getWindowSize(int *rows, int *cols)
{
    struct winsize ws;

    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1 || ws.ws_col == 0)
    {
        if(write(STDOUT_FILENO, "\x1b[999C\x1b[999B", 12) != 12)
            return false;

        return Fed_Terminal_getCursorPosition(rows, cols);
    }      

    *cols = ws.ws_col;
    *rows = ws.ws_row;

    return true;
}