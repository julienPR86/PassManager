#include "../headers/manager.h"

char	*get_setting_value(char *setting_name)
{
	char	*value;
	t_uint	index;

	if (NULL == setting_name)
		return (NULL);
	index = 0;
	while (*(settings_file_content + index))
	{
		value = get_word(*(settings_file_content + index), 0, "\t ");
		if (!strcmp(setting_name, value))
		{
			free(value);
			return (get_word(*(settings_file_content + index), 1, "\t "));
		}
		free(value);
		index++;
	}
	return (NULL);
}

int	change_setting_value(char *setting_name)
{
	if (NULL == setting_name)
		return (FAILURE);
	return (SUCCESS);
}