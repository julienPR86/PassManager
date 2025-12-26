#include "../headers/manager.h"

int	update_history(char	**args)
{
	const char	*separation = " ";
	char		*line;
	t_uint		index;
	t_uint		size;

	if (NULL == args)
		return (FAILURE);
	size = 0;
	index = 0;
	while (*(args + index))
	{
		size += strlen(*(args + index));
		++index;
	}
	line = (char *)malloc(sizeof(char) * (size + (strings_size(args) - 1) * strlen(separation) + 1));
	if (NULL == line)
		return (FAILURE);
	*line = '\0';
	index = 0;
	while (*(args + index))
	{
		strcat(line, *(args + index));
		if (*(args + index + 1))
			strcat(line, separation);
		++index;
	}
	*(line + size + strings_size(args) - 1) = '\0';
	if (!strcmp(*args, "add"))
		replace_word(line, 3, "\t ", '*');
	else if (!strcmp(*args, "replace"))
		replace_word(line, 4, "\t ", '*');
	strs_add_line(&history_file_content, line);
	free(line);
	return (SUCCESS);
}
