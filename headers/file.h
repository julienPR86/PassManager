#ifndef _FILE_
#define _FILE_

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

/*read the file passed in, and return a arrray of strings*/
char **read_file(FILE *file);

/*get the number of lines of the file passed in*/
int get_height(FILE *file);

/*return the length of the longest line of the file passed in*/
int get_width(FILE *file);

/*write the text in the file passed in*/
int write_file(FILE *file, char **text, int height);

#endif