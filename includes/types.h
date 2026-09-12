#ifndef TYPES_H
# define TYPES_H

# define MAX_STRING_LENGTH 256
# define COMMAND_COUNT 9
# define MAX_ALIAS_NUM 3
# define MAX_SUB_COMMAND_NUM 3

typedef unsigned int	t_uint;

typedef enum	e_exit_status
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
}	t_status;

typedef enum	e_output_type
{
	MESSAGE,
	WARNING,
	ERROR,
}	t_output_type;

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

#endif
