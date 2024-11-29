#ifndef _STR_
#define _STR_

#include "vars.h"

/*compare to characters
You can modify their value by puting a number in n1 or n2*/
int charcmp(char c1, char c2, int n1, int n2);

/*sort two string
returns 0 if the strings a sorted, otherwise it returns 1*/
int str_sort(char *str1, char *str2);

/*sort an array of strings*/
char **sort(char **strings);

#endif