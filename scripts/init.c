#include "../headers/manager.h"

int		rewrite_data_file = 0;
char	*data_file_name = "data/data.txt";
char	**data_file_content = NULL;

int	init(void)
{
	FILE	*file;

	file = fopen(data_file_name, "r");
	if (NULL == file)
		return (COULD_NOT_OPEN_FILE);
	data_file_content = read_file(file);
	if (NULL == data_file_content)
	{
		fclose(file);
		return (FAILED_TO_READ_DATA);
	}
	fclose(file);
	sort_strings(data_file_content);
	return (SUCCESS);
}