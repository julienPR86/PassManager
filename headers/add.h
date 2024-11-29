#ifndef _ADD_
#define _ADD_

#include <stdio.h>

/*add a password to the database*/
int add_command(char *name, char *identifier, char *password, char ***text, char *separation, int *height, int *width, int overwrite);

/*add a password to the database*/
int add_pass(char *name, char *identifier, char *password, char ***text, char *separation, int *height);

/*overwrite a password already existing*/
int overwrite_pass(char *name, char *identifier, char *password, char ***text, char *separation, int line);

#endif