#include "manager.h"

void	exit_program(void)
{
	strDestroy(data_file_content);
	strDestroy(settings_file_content);
	strDestroy(history_file_content);
	return ;
}
