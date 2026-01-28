#include "../includes/manager.h"

int get_file_content(char *path, char ***strings)
{
	FILE	*file;

	if (NULL == path || NULL == strings)
		return (FAILURE);
	file = fopen(path, "r");
	if (NULL == file)
		return (COULD_NOT_OPEN_FILE);
	*strings = read_file(file);
	fclose(file);
	if (NULL == *strings)
		return (FAILED_TO_READ_FILE);
	return (SUCCESS);
}

char	**read_file(FILE *file)
{
	char	**data;
	char	c;
	t_uint	width;
	t_uint	height;
	t_uint	line_index;
	t_uint	write_index;

	if (NULL == file)
		return (NULL);
	file_dimensions(file, &width, &height);
	data = (char **)malloc(sizeof(char *) * (height + 1));
	if (NULL == data)
		return (NULL);
	line_index = 0;
	while (line_index < height)
	{
		*(data + line_index) = (char *)malloc(sizeof(char) * (width + 1));
		if (NULL == *(data + line_index))
		{
			free_strings(data);
			return (NULL);
		}
		line_index++;
	}
	c = 0;
	line_index = 0;
	while (line_index < height)
	{
		write_index = 0;
		c = getc(file);
		while (c != EOF && c != '\n')
		{
			*(*(data + line_index) + write_index) = c;
			write_index++;
			c = getc(file);
		}
		*(*(data + line_index) + write_index) = '\0';
		if (write_index)
			line_index++;
	}
	*(data + height) = NULL;
	rewind(file);
	return (data);
}

int	rewrite_file(char *path, char **content)
{
	FILE	*file;
	t_uint	index;

	if (NULL == path || NULL == content)
		return (FAILURE);
	file = fopen(path, "w");
	if (NULL == file)
		return (COULD_NOT_OPEN_FILE);
	sort_strings(content);
	index = 0;
	while (*(content + index))
	{
		if (!*(content + index + 1))
		{
			fprintf(file, "%s", *(content + index));
			break;
		}
		fprintf(file, "%s\n", *(content + index));
		index++;
	}
	fclose(file);
	return (SUCCESS);
}

int	file_dimensions(FILE *file, t_uint *w, t_uint *h)
{
	char			c;
	t_uint	width;

	if (NULL == file || NULL == w || NULL == h)
		return (FAILURE);
	c = 0;
	*h = 1;
	*w = 0;
	width = 0;
	while (1)
	{
		c = getc(file);
		if (EOF == c)
			break;
		if (c == '\n')
		{
			if (!width)
				continue;
			if (width > *w)
				*w = width;
			(*h)++;
			width = 0;
			continue;
		}
		width++;
	}
	if (width > *w)
	{
		*w = width;
		if (*h == 0)
			(*h)++;
	}
	if (width == 0)
		(*h)--;
	if (*w == 0)
		*h = 0;
	rewind(file);
	return (SUCCESS);
}
