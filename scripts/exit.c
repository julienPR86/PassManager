#include "../headers/manager.h"

void	exit_program(void)
{
	free_strings(data_file_content);
	free_strings(settings_file_content);
	return ;
}