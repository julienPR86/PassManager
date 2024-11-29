#ifndef _VARS_
#define _VARS_

#include <stdio.h>
#include "file.h"
#include "str.h"

const char *separation;
const char *filename;

int running;

int text_height;
int text_width;
char **text;

/*init all the global variables*/
int init(void);

#endif