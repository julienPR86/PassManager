#include "../headers/manager.h"

int	manager(void)
{
	int		run;
	char	*command;
	char	**args;
	char	*data_file_path;

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
		if (COULD_NOT_OPEN_FILE == rewrite_file(data_file_path, data_file_content))
			error_output("Failed to rewrite data file\n");
		free(data_file_path);
	}
	if (rewrite_settings_file)
	{
		if (COULD_NOT_OPEN_FILE == rewrite_file(SETTINGS_PATH, settings_file_content))
			error_output("Failed to rewrite settings file\n");
	}
	return (SUCCESS);
}

int	main(void)
{
	switch (init())
	{
		case INITIALISATION_FAILED:
			error_output("Could not initialise the program\n");
			return (FAILURE);
		case COULD_NOT_OPEN_SETTINGS_FILE:
			error_output("Could not open settings file\n");
			return (FAILURE);
		case FAILED_TO_READ_SETTINGS_FILE:
			error_output("Failed to read the settings file\n");
			return (FAILURE);
		case COULD_NOT_OPEN_FILE:
			error_output("Could not open data file\n");
			break;
		case FAILED_TO_READ_FILE:
			error_output("Failed to read content file\n");
			return (FAILURE);
		default:
			break;
	}
	manager();
	exit_program();
	return (SUCCESS);
}
