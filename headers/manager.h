#ifndef _MANAGER_
#define _MANAGER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "add.h"
#include "file.h"
#include "get.h"
#include "help.h"
#include "inputs.h"
#include "list.h"
#include "utils.h"
#include "remove.h"
#include "str.h"

/*run a command that can affect text*/
int run_command(char *_command, char ***text, char *separation, int *height, int *width, int *running, int *rewrite);

#endif