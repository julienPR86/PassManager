#ifndef MANAGER_H
# define MANAGER_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# define MAX_STRING_LENGTH 256
# define COMMAND_COUNT 8
# define MAX_ALIAS_NUM 3
# define MAX_SUB_COMMAND_NUM 3

# define SETTINGS_PATH "data/settings/settings.txt"

# define ISPRINT(c) (((c) >= 32) && ((c) <= 126))
# define ISRIGHT(c) (((c) != '$') && ((c) != ';') && ((c) != '|') && ((c) != '&'))

enum	ERROR_CODES
{
	SUCCESS,
	FAILURE,
	INITIALISATION_FAILED,
	COULD_NOT_OPEN_FILE,
	COULD_NOT_OPEN_SETTINGS_FILE,
	FAILED_TO_READ_SETTINGS_FILE,
	FAILED_TO_READ_DATA_FILE,
	DATABASE_EMPTY,
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
	char				*name;
	char				*alias[MAX_ALIAS_NUM];
	t_uint				min_args;
	t_uint				max_args;
	int					(*command)(char **);
	struct s_Command	*sub_commands[MAX_SUB_COMMAND_NUM];
}	t_Command;

extern int			rewrite_data_file;
extern char			**data_file_content;
extern char			**settings_file_content;
extern t_Command	commands[COMMAND_COUNT];

//Init functions

int		init(void);

//Exit functions

void	exit_program(void);

//Execute functions

int		execute_cmd(char **args);
int		check_cmd_args_number(char **args, t_Command *command);

//Commands functions

int		list_cmd(char **args);
int		get_cmd(char **args);
int		add_cmd(char **args);
int		replace_cmd(char **args);
int		remove_cmd(char **args);
int		data_cmd(char **args);
int		help_cmd(char **args);
int		exit_cmd(char **args);

//Pass commands

t_Pass	*get_pass(char *name);
int		get_pass_index(char **content, char *name);
void	display_pass(t_Pass *pass);
void	free_pass(t_Pass *pass);

//Files functions

char	**read_file(FILE *file);
int		rewrite_file(char *path, char **content);
int		file_dimensions(FILE *file, t_uint *w, t_uint *h);

//Inputs functions

char	*input(char *msg);
void	empty_stdin(void);

//Outputs functions

void	message_output(char *msg);
void	error_output(char *error);

//Settings functions

char	*get_setting(char *name);

//Utils functions

int		is_cmd_valid(char *cmd);
char	*get_cmd_name(char *alias);
char	**sort_strings(char **strings);
char	**split_string(char *str, char *set);
char	*get_word(char *str, int word_index, char *set);
t_uint	count_words(char *str, char *set);
t_uint	strings_size(char **strings);
void	free_strings(char **strs);

#endif