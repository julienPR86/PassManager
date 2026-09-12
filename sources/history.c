#include "manager.h"

int	update_history(char	**args)
{
	const char	*separation = " ";
	char		*line;

	if (NULL == args)
		return (FAILURE);
	line = strJoin((const char **)args, separation);
	if (NULL == line)
		return (FAILURE);
	if (!strCompare(*args, "add"))
		replace_word(line, 3, "\t ", '*');
	else if (!strCompare(*args, "replace"))
		replace_word(line, 4, "\t ", '*');
	strs_add_line(&history_file_content, line);
	free(line);
	return (SUCCESS);
}
