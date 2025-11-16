#include "../headers/manager.h"

int	manager(void)
{
	int		run;
	char	*command;

	printf("Tap help for more informations\n");
	run = 1;
	while (run)
	{
		command = input("$>");
		if (NULL == command)
			continue ;
		switch (execute_cmd(command))
		{
			case EXIT_PROGRAM:
				run = 0;
				break;
			default:
				break;
		}
		free(command);
	}
	if (rewrite_data_file)
		rewrite_file(data_file_content);
	return (SUCCESS);
}

int	main(void)
{
	switch (init())
	{
		case INITIALISATION_FAILED:
			error_output("Could not initialise the program\n");
			return (FAILURE);
		case COULD_NOT_OPEN_FILE:
			error_output("Could not open data file\n");
			return (FAILURE);
		case FAILED_TO_READ_DATA:
			error_output("Failed to read the data\n");
			return (FAILURE);
		default:
			break;
	}
	manager();
	exit_program();
	return (SUCCESS);
}
