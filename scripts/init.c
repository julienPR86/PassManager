#include "../headers/manager.h"

int		rewrite_data_file;
int		rewrite_settings_file;
char	**data_file_content;
char	**settings_file_content;

int	init(void)
{
	char	*data_file_path;

	rewrite_data_file = 0;
	rewrite_settings_file = 0;
	data_file_content = NULL;
	settings_file_content = NULL;
	switch (get_file_content(SETTINGS_PATH, &settings_file_content))
	{
		case COULD_NOT_OPEN_FILE :
			return (COULD_NOT_OPEN_SETTINGS_FILE);
		case FAILED_TO_READ_FILE :
			return (FAILED_TO_READ_SETTINGS_FILE);
		default :
			break;
	}
	data_file_path = get_setting_value("data_path");
	switch (get_file_content(data_file_path, &data_file_content))
	{
		case COULD_NOT_OPEN_FILE :
			free(data_file_path);
			return (COULD_NOT_OPEN_FILE);
		case FAILED_TO_READ_FILE :
			free(data_file_path);
			free_strings(settings_file_content);
			return (FAILED_TO_READ_FILE);
		default :
			break;
	}
	free(data_file_path);
	sort_strings(data_file_content);
	return (SUCCESS);
}
