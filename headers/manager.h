#ifndef MANAGER_H
# define MANAGER_H

# include <stdio.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <time.h>

# define MAX_STRING_LENGTH 256
# define COMMAND_COUNT 9
# define MAX_ALIAS_NUM 3
# define MAX_SUB_COMMAND_NUM 3

# define SETTINGS_PATH "data/settings/settings.txt"

enum	ERROR_CODES
{
	SUCCESS,
	FAILURE,
	INITIALISATION_FAILED,
	COULD_NOT_OPEN_FILE,
	COULD_NOT_OPEN_SETTINGS_FILE,
	FAILED_TO_READ_SETTINGS_FILE,
	FAILED_TO_READ_FILE,
	FAILED_FILE_REWRITE,
	DATABASE_EMPTY,
	SETTING_NOT_FOUND,
	COMMAND_NOT_FOUND,
	WRONG_COMMAND_ARG_NUM,
	ENTRY_NOT_FOUND,
	ENTRY_ALREADY_EXISTS,
	HELP_ENTRY_NOT_FOUND,
	FAILED_PASSWORD_GEN,
	EXIT_PROGRAM,
};

enum	OUTPUT_TYPES
{
	MESSAGE,
	WARNING,
	ERROR,
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
	int					(*command)(char **, struct s_Command *[]);
	struct s_Command	*sub_commands[MAX_SUB_COMMAND_NUM];
}	t_Command;

extern int			rewrite_data_file;
extern int			rewrite_settings_file;
extern int			rewrite_history_file;
extern char			**data_file_content;
extern char			**settings_file_content;
extern char			**history_file_content;
extern t_Command	*commands[COMMAND_COUNT];

//Init functions

int		init(void);

//Exit functions

void	exit_program(void);

//Execute functions

int		execute_cmd(char **args, t_Command *commands_array[]);
int		check_cmd_args_number(char **args, t_Command *command);

//Commands functions

int		list_cmd(char **args, t_Command *commands_array[]);
int		get_cmd(char **args, t_Command *commands_array[]);
int		add_cmd(char **args, t_Command *commands_array[]);
int		replace_cmd(char **args, t_Command *commands_array[]);
int		remove_cmd(char **args, t_Command *commands_array[]);
int		data_cmd(char **args, t_Command *commands_array[]);
int		history_cmd(char **args, t_Command *commands_array[]);
int		help_cmd(char **args, t_Command *commands_array[]);
int		exit_cmd(char **args, t_Command *commands_array[]);

//Sub-commands functions

int		data_change_cmd(char **args, t_Command *commands_array[]);

//Pass commands

t_Pass	*get_pass(char *name);
int		get_pass_index(char **content, char *name);
void	display_pass(t_Pass *pass);
void	free_pass(t_Pass *pass);

//Files functions

int 	get_file_content(char *path, char ***strings);
char	**read_file(FILE *file);
int		rewrite_file(char *path, char **content);
int		file_dimensions(FILE *file, t_uint *w, t_uint *h);

//Inputs functions

char	*input(char *msg);
void	empty_stdin(void);

//Outputs functions

void	message_output(int type, char *msg, ...);

//Settings functions

char	*get_setting_value(char *setting_name);
int		get_setting_value_index(char *setting_name);
int		change_setting_value(char *setting_name, char *value);

//History functions

int		update_history(char	**args);

//Password generator

char	*gen_pw(t_uint len);

//Utils functions

char	*get_cmd_name(char *alias, t_Command *commands_array[]);
char	**split_string(char *str, char *set);
char	*get_word(char *str, int word_index, char *set);
t_uint	count_words(char *str, char *set);
char	*replace_word(char *str, t_uint word_index, char *set, char replace_char);
char	**sort_strings(char **strings);
int		strcompare(char *s1, char *s2);
int		strs_add_line(char ***strs, char *line);
char	*strshuffle(char *str);
t_uint	strings_size(char **strings);
void	free_strings(char **strs);

#endif