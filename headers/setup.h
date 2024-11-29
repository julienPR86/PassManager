#ifndef _SETUP_
#define _SETUP_

#include <stdio.h>
#include "file.h"
#include "str.h"

extern const char *separation;
extern const char *filename;

extern int running;

extern int text_height;
extern int text_width;
extern char **text;

/*init all the global variables*/
int init(void);

#endif