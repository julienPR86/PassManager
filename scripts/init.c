#include "../headers/manager.h"

int		rewrite_data_file;
int		rewrite_settings_file;
char	**data_file_content;
char	**settings_file_content;

int	init(void)
{
	FILE	*data_file;
	FILE	*settings_file;
	char	*data_file_path;

	rewrite_data_file = 0;
	rewrite_settings_file = 0;
	data_file_content = NULL;
	settings_file_content = NULL;
	settings_file = fopen(SETTINGS_PATH, "r");
	if (NULL == settings_file)
		return (COULD_NOT_OPEN_SETTINGS_FILE);
	settings_file_content = read_file(settings_file);
	if (NULL == settings_file_content)
	{
		fclose(settings_file);
		return (FAILED_TO_READ_SETTINGS_FILE);
	}
	fclose(settings_file);
	data_file_path = get_setting_value("data_path");
	data_file = fopen(data_file_path, "r");
	if (NULL == data_file)
	{
		free(data_file_path);
		return (COULD_NOT_OPEN_FILE);
	}
	data_file_content = read_file(data_file);
	if (NULL == data_file_content)
	{
		fclose(data_file);
		free(data_file_path);
		free_strings(settings_file_content);
		return (FAILED_TO_READ_DATA_FILE);
	}
	fclose(data_file);
	free(data_file_path);
	sort_strings(data_file_content);
	return (SUCCESS);
}