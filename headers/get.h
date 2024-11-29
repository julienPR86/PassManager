#ifndef _GET_
#define _GET_

#include <stdio.h>

#if defined(_WIN32) || defined(_WIN64)
    #define CLIPBOARD_CMD "clip"
#elif defined(__APPLE__) && defined(__MACH__)
    #define CLIPBOARD_CMD "pbcopy"
#elif defined(__linux__)
    #define CLIPBOARD_CMD "xclip -selection clipboard"
#else
    #error "Unsupported OS"
#endif

/*get the identifier and the password of the name passed in*/
int get_command(char *name, char **text, char *separation, int height);

/*get the identifier and the password of the name passed in*/
int get_pass(char *name, char **text, char *separation, int height);

#endif