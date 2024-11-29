#ifndef _REMOVE_
#define _REMOVE_

#include <stdio.h>
#include <stdlib.h>
#include "str.h"
#include "utils.h"
/*remove a password based on the name passed in*/
int remove_command(char *name, char ***text, char *separation, int *height, int *width);

/*remove a password based on the name passed in*/
int remove_pass(char *name, char ***text, char *separation, int *height, int width);

#endif