#include "../headers/manager.h"

int	manager(void)
{
	int		run;
	char	*command;
	char	**args;
	char	*data_file_path;
	char	*history_file_path;

	run = 1;
	while (run)
	{
		command = input("$>");
		if (NULL == command)
			continue ;
		args = split_string(command, "\t ");
		switch (execute_cmd(args, commands))
		{
			case EXIT_PROGRAM:
				run = 0;
				break;
			default:
				break;
		}
		free_strings(args);
		free(command);
	}
	if (rewrite_data_file)
	{
		data_file_path = get_setting_value("data_path");
		if (SUCCESS != rewrite_file(data_file_path, data_file_content))
			message_output(ERROR, "Failed to rewrite data file.");
		free(data_file_path);
	}
	if (rewrite_history_file)
	{
		history_file_path = get_setting_value("history_path");
		if (SUCCESS != rewrite_file(history_file_path, history_file_content))
			message_output(ERROR, "Failed to rewrite history file.");
		free(history_file_path);
	}
	if (rewrite_settings_file)
	{
		if (SUCCESS != rewrite_file(SETTINGS_PATH, settings_file_content))
			message_output(ERROR, "Failed to rewrite settings file.");
	}
	return (SUCCESS);
}

int	main(void)
{
	switch (init())
	{
		case INITIALISATION_FAILED:
			return (FAILURE);
		case COULD_NOT_OPEN_SETTINGS_FILE:
			return (FAILURE);
		case FAILED_TO_READ_SETTINGS_FILE:
			return (FAILURE);
		case FAILED_TO_READ_FILE:
			return (FAILURE);
		default:
			break;
	}
	manager();
	exit_program();
	return (SUCCESS);
}
