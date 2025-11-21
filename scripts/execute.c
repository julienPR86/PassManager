#include "../headers/manager.h"

int	execute_cmd(char **args, t_Command *commands_array[])
{
	t_uint		index;
	int			(*command_func)(char **, t_Command *[]);
	t_Command	**sub_commands;

	if (NULL == args || NULL == commands_array)
		return (FAILURE);
	index = 0;
	command_func = NULL;
	while (*args && *(commands_array + index) && index < COMMAND_COUNT)
	{
		if (!strcmp(*args, (*(commands_array + index))->name))
		{
			command_func = (*(commands_array + index))->command;
			sub_commands = (*(commands_array + index))->sub_commands;
			break;
		}
		for (int i = 0; i < MAX_ALIAS_NUM; i++)
		{
			if (!*((*(commands_array + index))->alias + i))
				break ;
			if (strcmp(*args, *((*(commands_array + index))->alias + i)))
				continue ;
			command_func = (*(commands_array + index))->command;
			sub_commands = (*(commands_array + index))->sub_commands;
			break ;
		}
		if (NULL != command_func)
			break;
		index++;
	}
	if (NULL == command_func)
	{
		error_output("Command not found\n");
		return (COMMAND_NOT_FOUND);
	}
	if (check_cmd_args_number(args, *(commands_array + index)))
	{
		error_output("Wrong arguments number\n");
		return (WRONG_COMMAND_ARG_NUM);
	}
	switch (command_func(args + 1, sub_commands))
	{
		case DATABASE_EMPTY:
			error_output("There is no entries in database\n");
			break;
		case COMMAND_NOT_FOUND:
			error_output("Unknow command\n");
			break;
		case ENTRY_NOT_FOUND:
			error_output("Unknow entry\n");
			break;
		case ENTRY_ALREADY_EXISTS:
			error_output("Entry already exists in database\n");
			break;
		case HELP_ENTRY_NOT_FOUND:
			error_output("Help about this command does not exists\n");
			break;
		case FAILED_PASSWORD_GEN:
			error_output("Failed to generate random password\n");
			break;
		case EXIT_PROGRAM:
			return (EXIT_PROGRAM);
		default:
			break ;
	}
	return (SUCCESS);
}

int	check_cmd_args_number(char **args, t_Command *cmd)
{
	t_uint	args_num;

	if (NULL == args || NULL == cmd)
		return (FAILURE);
	args_num = 0;
	while (*(args + args_num))
		args_num++;
	if (args_num - 1 > cmd->max_args || args_num - 1 < cmd->min_args)
		return (WRONG_COMMAND_ARG_NUM);
	return (SUCCESS);
}
