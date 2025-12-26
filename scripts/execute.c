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
		message_output(ERROR, "Command not found.");
		return (COMMAND_NOT_FOUND);
	}
	if (check_cmd_args_number(args, *(commands_array + index)))
	{
		message_output(ERROR, "Wrong arguments number.");
		return (WRONG_COMMAND_ARG_NUM);
	}
	switch (command_func(args + 1, sub_commands))
	{
		case DATABASE_EMPTY:
			message_output(MESSAGE, "There is no entries in database.");
			break;
		case COMMAND_NOT_FOUND:
			message_output(ERROR, "Unknow command.");
			break;
		case ENTRY_NOT_FOUND:
			message_output(ERROR, "Unknow entry.");
			break;
		case ENTRY_ALREADY_EXISTS:
			message_output(WARNING, "Entry already exists in database.");
			break;
		case HELP_ENTRY_NOT_FOUND:
			message_output(ERROR, "Help about this command does not exists.");
			break;
		case FAILED_PASSWORD_GEN:
			message_output(ERROR, "Failed to generate random password.");
			break;
		case EXIT_PROGRAM:
			update_history(args);
			rewrite_history_file = 1;
			return (EXIT_PROGRAM);
		default:
			break ;
	}
	update_history(args);
	rewrite_history_file = 1;
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
