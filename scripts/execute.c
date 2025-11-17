#include "../headers/manager.h"

int	execute_cmd(char *cmd)
{
	char	**args;
	t_uint	index;
	int		(*command_func)(char **);

	if (NULL == cmd)
		return (FAILURE);
	args = split_strings(cmd, "\t ");
	index = 0;
	command_func = NULL;
	while (*args && index < COMMAND_COUNT && NULL == command_func)
	{
		if (!strcmp(*args, (*(commands + index)).name))
		{
			command_func = (*(commands + index)).command;
			break;
		}
		for (int i = 0; i < MAX_ALIAS_NUM; i++)
		{
			if (!*((*(commands + index)).alias + i))
				break ;
			if (strcmp(*args, *((*(commands + index)).alias + i)))
				continue ;
			command_func = (*(commands + index)).command;
			break ;
		}
		if (NULL != command_func)
			break;
		index++;
	}
	if (NULL == command_func)
	{
		error_output("Command not found\n");
		free_strings(args);
		return (COMMAND_NOT_FOUND);
	}
	if (check_cmd_args_number(args, commands + index))
	{
		error_output("Wrong arguments number\n");
		free_strings(args);
		return (WRONG_COMMAND_ARG_NUM);
	}
	switch (command_func(args + 1))
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
		case EXIT_PROGRAM:
			free_strings(args);
			return (EXIT_PROGRAM);
		default:
			break ;
	}
	free_strings(args);
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
