#ifndef _ADD_
#define _ADD_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "str.h"
#include "vars.h"

/*add a password to the database*/
int add_command(char *name, char *identifier, char *password, int overwrite);

/*add a password to the database*/
int add_pass(char *name, char *identifier, char *password);

/*overwrite a password already existing*/
int overwrite_pass(char *name, char *identifier, char *password, int line);

#endif