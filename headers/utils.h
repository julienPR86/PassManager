#ifndef _UTILS_
#define _UTILS_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Check if name is in text
return 0 if not found, otherwise, it return the line where it is*/
int exist(char **text, char *name, char *separation, int height);

/*get the number of words contain in str*/
int get_words_num(char *str);

/*return a plateform name contain in str*/
char *get_plateform_name(char *str, char *separation);

/*Display an error message passed in*/
int error_msg(char *message);

#endif