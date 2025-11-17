#include "../headers/manager.h"

char	*get_setting(char *name)
{
	char	*setting;
	t_uint	index;

	if (NULL == name)
		return (NULL);
	index = 0;
	while (*(settings_file_content + index))
	{
		setting = get_word(*(settings_file_content + index), 0, "\t ");
		if (!strcmp(name, setting))
		{
			free(setting);
			return (get_word(*(settings_file_content + index), 1, "\t "));
		}
		free(setting);
		index++;
	}
	return (NULL);
}