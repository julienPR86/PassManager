#include "../headers/manager.h"

int		rewrite_data_file;
int		rewrite_settings_file;
int		rewrite_history_file;
char	**data_file_content;
char	**settings_file_content;
char	**history_file_content;

int	init(void)
{
	char	*data_file_path;
	char	*history_file_path;

	rewrite_data_file = 0;
	rewrite_settings_file = 0;
	rewrite_history_file = 0;
	data_file_content = NULL;
	settings_file_content = NULL;
	history_file_content = NULL;
	switch (get_file_content(SETTINGS_PATH, &settings_file_content))
	{
		case COULD_NOT_OPEN_FILE :
			message_output(WARNING, "Failed to open settings file.");
			return (COULD_NOT_OPEN_SETTINGS_FILE);
		case FAILED_TO_READ_FILE :
			message_output(ERROR, "Failed to read settings file.");
			return (FAILED_TO_READ_SETTINGS_FILE);
		default :
			break;
	}
	data_file_path = get_setting_value("data_path");
	if (NULL == data_file_path)
		return (SETTING_NOT_FOUND);
	switch (get_file_content(data_file_path, &data_file_content))
	{
		case COULD_NOT_OPEN_FILE :
			message_output(WARNING, "No data available.");
			break ;
		case FAILED_TO_READ_FILE :
			message_output(ERROR, "Failed to read data file.");
			return (FAILED_TO_READ_FILE);
		default :
			break;
	}
	free(data_file_path);
	history_file_path = get_setting_value("history_path");
	if (NULL == history_file_path)
		return (SETTING_NOT_FOUND);
	switch (get_file_content(history_file_path, &history_file_content))
	{
		case COULD_NOT_OPEN_FILE :
			message_output(WARNING, "No history available.");
			break ;
		case FAILED_TO_READ_FILE :
			message_output(ERROR, "Failed to read history file.");
			return (FAILED_TO_READ_FILE);
		default :
			break ;
	}
	free(history_file_path);
	srand(time(NULL) * (strings_size(data_file_content) + 1));
	sort_strings(data_file_content);
	return (SUCCESS);
}
