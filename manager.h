#ifndef _MANAGER_H_
#define _MANAGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256

#if defined(_WIN32) || defined(_WIN64)
    #define CLIPBOARD_CMD "clip"
#elif defined(__APPLE__) && defined(__MACH__)
    #define CLIPBOARD_CMD "pbcopy"
#elif defined(__linux__)
    #define CLIPBOARD_CMD "xclip -selection clipboard"
#else
    #error "Unsupported OS"
#endif

extern const char *separation;
extern const char *filename;
extern int running;
extern int text_height;
extern int text_width;
/*the variable which contains all the passwords*/
extern char **text;
extern int rewrite;

/*init all variables about the text*/
int init();

/*read a file passed in and return a string array*/
char **read_file(FILE *file);

/*get the number of line and the longest line of a file passed in*/
void get_dimensions(FILE *file, int *height, int *width);

/*write the content of text in the file passed in*/
int write_file();

/*check if name exist in text*/
int exist(char *name);

/*return the words number in a string*/
int get_words_num(char *string);

/*return a string which is a name of a plateform*/
char *get_plateform_name(char *str);

/*compare to characters, they can be modify with value1 and value2*/
int charcmp(char chr1, char chr2, int value1, int value2);

/*return 0 if str1 if lower than str2, otherwise it return 1*/
int str_sort(char *str1, char *str2);

/*sort a string array*/
char **sort(char **text);

/*remove page in text*/
int remove_command(char *page);

/*remove page in text*/
int remove_pass(char *name);

/*execute the command passed in*/
int run_command(char *_command);

/*get the words of a string*/
char **get_args(char *command);

/*free the args array's strings*/
void free_args(char **args, int length);

/*list all plateform's name available*/
int list_command();

/*return a string write by the user*/
char *input(char *str, int returns);

/*make the stdin empty*/
void empty_stdin();

/*display help about the commands*/
int help(char *command);

/*return a page name, identifier, and password from the page passed in*/
int get_pass(char *name);

/*add a page, identifier, and password in text*/
int add_command(char *page, char *identifier, char *password, int overwrite);

/*add a page, identifier, and password in text*/
int add_pass(char *name, char *identifier, char *password);

/*overwrite a page, identifier, and password in text*/
int overwrite_pass(char *name, char *identifier, char *password, int line_num);

/*return a string, source, created with args*/
char *string(char *source, char **args, int args_length);

/*display message as an error msg*/
void error_msg(char *message);

#endif