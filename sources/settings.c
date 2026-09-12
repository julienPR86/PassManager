#include "manager.h"

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
		if (NULL != value && !strCompare(setting_name, value))
		{
			free(value);
			return (get_word(*(settings_file_content + index), 1, "\t "));
		}
		free(value);
		index++;
	}
	return (NULL);
}

int	get_setting_value_index(char *setting_name)
{
	char	*value;
	int		index;

	if (NULL == setting_name)
		return (-1);
	index = 0;
	while (*(settings_file_content + index))
	{
		value = get_word(*(settings_file_content + index), 0, "\t ");
		if (!strCompare(setting_name, value))
		{
			free(value);
			return (index);
		}
		free(value);
		index++;
	}
	return (-1);
}

int	change_setting_value(char *setting_name, char *value)
{
	const char	*separation = " ";
	int			setting_index;
	char		*setting_save;
	char		*setting;
	char		*tmp;
	const char	*null_value = "none";

	if (NULL == setting_name)
		return (FAILURE);
	setting_index = get_setting_value_index(setting_name);
	if (-1 == setting_index)
		return (FAILURE);
	if (NULL == value)
		value = (char *)null_value;
	setting = *(settings_file_content + setting_index);
	setting_save = setting;
	setting = strDup(setting_name);
	if (NULL == setting)
	{
		setting = setting_save;
		return (FAILURE);
	}
	tmp = strAppend(setting, separation);
	free(setting);
	if (NULL == tmp)
	{
		setting = setting_save;
		return (FAILURE);
	}
	setting = strAppend(tmp, value);
	free(tmp);
	if (NULL == setting)
	{
		setting = setting_save;
		return (FAILURE);
	}
	free(setting_save);
	*(settings_file_content + setting_index) = setting;
	rewrite_settings_file = 1;
	return (SUCCESS);
}
