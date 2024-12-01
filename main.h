#ifndef _MANAGER_
#define _MANAGER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256


extern const char *separation;
extern const char *filename;
extern int running;
extern int text_height;
extern int text_width;
extern char **text;

char **read_file(FILE *file);
int get_height(FILE *file);
int get_width(FILE *file);
int write_file(FILE *file);
int exist(char *name);
int get_words_num(char *string);
char *get_plateform_name(char *str);
int charcmp(char chr1, char chr2, int value1, int value2);
int str_sort(char *str1, char *str2);
char **sort(char **text);
int remove_command(char *page);
int remove_pass(char *name);
int run_command(char *_command, int *rewrite);
int list_command();
char *input(char *str, int returns);
int help(char *command);
int get_command(char *page);
int get_pass(char *name);
int add_command(char *page, char *identifier, char *password, int overwrite);
int add_pass(char *name, char *identifier, char *password);
int overwrite_pass(char *name, char *identifier, char *password, int line_num);
void error_msg(char *message);

#endif