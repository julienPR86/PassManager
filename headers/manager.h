#ifndef MANAGER_H
# define MANAGER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAX_STRING_LENGTH 256
# define COMMAND_COUNT 7
# define MAX_ALIAS_NUM 3

# define ISPRINT(c) (((c) >= 32) && ((c) <= 126))
# define ISRIGHT(c) (((c) != '$') && ((c) != ';') && ((c) != '|') && ((c) != '&'))

enum	ERROR_CODES
{
	SUCCESS,
	FAILURE,
	INITIALISATION_FAILED,
	FAILED_TO_READ_DATA,
	DATABASE_EMPTY,
	COULD_NOT_OPEN_FILE,
	COMMAND_NOT_FOUND,
	WRONG_COMMAND_ARG_NUM,
	ENTRY_NOT_FOUND,
	ENTRY_ALREADY_EXISTS,
	HELP_ENTRY_NOT_FOUND,
	EXIT_PROGRAM,
};

typedef unsigned int	t_uint;

typedef struct s_Pass
{
	char	*name;
	char	*identifier;
	char	*password;
}	t_Pass;


typedef struct s_Command
{
	char	*name;
	char	*alias[MAX_ALIAS_NUM];
	t_uint	min_args;
	t_uint	max_args;
	int		(*command)(char **);
}	t_Command;

extern int			rewrite_data_file;
extern char			*data_file_name;
extern char			**data_file_content;
extern t_Command	commands[COMMAND_COUNT];

//Init functions

int	init(void);

//Exit functions

void	exit_program(void);

//Execute functions

int		execute_cmd(char *cmd);
int		check_cmd_args_number(char **args, t_Command *command);

//Commands functions

int		list_cmd(char **args);
int		get_cmd(char **args);
int		add_cmd(char **args);
int		replace_cmd(char **args);
int		remove_cmd(char **args);
int		help_cmd(char **args);
int		exit_cmd(char **args);

//Pass commands

t_Pass	*get_pass(char *name);
t_uint	get_pass_index(char **content, char *name);
void	display_pass(t_Pass *pass);
void	free_pass(t_Pass *pass);

//Files functions

char	**read_file(FILE *file);
int		rewrite_file(char **content);
int		file_dimensions(FILE *file, t_uint *w, t_uint *h);

//Inputs functions

char	*input(char *msg);
void	empty_stdin(void);

//Outputs functions

void	error_output(char *error);

//Utils functions

int		is_cmd_valid(char *cmd);
char	*get_cmd_name(char *alias);
char	**sort_strings(char **strings);
char	**split(char *str);
char	*get_word(char *str, int word_index);
t_uint	count_words(char *str);
t_uint	strings_size(char **strings);
void	free_strings(char **strs);

#endif