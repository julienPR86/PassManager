#ifndef _UTILS_
#define _UTILS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "setup.h"

/*Check if name is in text
return 0 if not found, otherwise, it return the line where it is*/
int exist(char *name);

/*get the number of words contain in str*/
int get_words_num(char *str);

/*return a plateform name contain in str*/
char *get_plateform_name(char *str);

/*Display an error message passed in*/
int error_msg(char *message);

#endif