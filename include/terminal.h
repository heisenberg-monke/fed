#ifndef FED_TERMINAL_H
#define FED_TERMINAL_H

void Fed_Terminal_failure(const char *s);

void Fed_Terminal_enableRawMode();
void Fed_Terminal_disableRawMode();

char Fed_Terminal_readKey();

#endif