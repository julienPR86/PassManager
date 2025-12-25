#include "../headers/manager.h"

int	is_cmd_valid(char *cmd)
{
	t_uint	index;

	if (NULL == cmd)
		return (0);
	index = 0;
	while (*(cmd + index))
	{
		if (!ISPRINT(*(cmd + index)) || !ISRIGHT(*(cmd + index)))
			return (0);
		index++;
	}
	return (1);
}

char	*get_cmd_name(char *alias, t_Command *commands_array[])
{
	t_uint	index;
	t_uint	alias_index;

	if (NULL == alias)
		return (NULL);
	index = 0;
	while (index < COMMAND_COUNT)
	{
		alias_index = 0;
		while (alias_index < MAX_ALIAS_NUM)
		{
			if (*((*(commands_array + index))->alias + alias_index) && !strcmp(alias, *((*(commands_array + index))->alias + alias_index)))
				return ((*(commands_array + index))->name);
			alias_index++;
		}
		if (!strcmp(alias, (*(commands_array + index))->name))
			return ((*(commands_array + index))->name);
		index++;
	}
	return (NULL);
}

char	*get_word(char *str, int word_index, char *set)
{
	char	*word;
	int		is_word;
	int		count;
	t_uint	index;
	t_uint	cpy_index;

	if (NULL == str || NULL == set)
		return (NULL);
	is_word = 1;
	count = -1;
	index = 0;
	while (*(str + index) && count < word_index)
	{
		if (strchr(set, *(str + index)))
			is_word = 1;
		else if (is_word)
		{
			count++;
			is_word = 0;
		}
		index++;
	}
	index--;
	cpy_index = 0;
	while (*(str + index + cpy_index) &&  !strchr(set, *(str + index + cpy_index)))
		cpy_index++;
	word = (char *)malloc(sizeof(char) * (cpy_index + 1));
	if (NULL == word)
		return (NULL);
	cpy_index = 0;
	while (*(str + index + cpy_index) && !strchr(set, *(str + index + cpy_index)))
	{
		*(word + cpy_index) = *(str + index + cpy_index);
		cpy_index++;
	}
	*(word + cpy_index) = '\0';
	return (word);
}

t_uint	count_words(char *str, char *set)
{
	t_uint	count;
	t_uint	index;
	int		is_word;

	if (NULL == str)
		return (0);
	is_word = 1;
	count = 0;
	index = 0;
	while (*(str + index))
	{
		if (strchr(set, *(str + index)))
			is_word = 1;
		else if (is_word)
		{
			count++;
			is_word = 0;
		}
		index++;
	}
	return (count);
}

char	**split_string(char *str, char *set)
{
	char	**strings;
	t_uint	wc;
	t_uint	start_index;
	t_uint	end_index;
	t_uint	counter;

	if (NULL == str || NULL == set)
		return (NULL);
	wc = count_words(str, set);
	strings = (char **)malloc(sizeof(char *) * (wc + 1));
	if (NULL == strings)
		return (NULL);
	counter = 0;
	end_index = 0;
	while (counter < wc)
	{
		start_index = end_index;
		while (*(str + start_index) && strchr(set, *(str + start_index)))
			start_index++;
		end_index = start_index;
		while (*(str + end_index) && !strchr(set, *(str + end_index)))
			end_index++;
		*(strings + counter) = strndup(str + start_index, end_index - start_index);
		if (NULL == *(strings + counter))
		{
			free_strings(strings);
			return (NULL);
		}
		counter++;
	}
	*(strings + counter) = NULL;
	return (strings);
}

char	**sort_strings(char **strings)
{
	char	*tmp;
	t_uint	i;
	t_uint	j;

	if (NULL == strings)
		return (NULL);
	i = 0;
	while (*(strings + i))
	{
		j = i;
		while (*(strings + j))
		{
			if (strcompare(*(strings + i), *(strings + j)) == 1)
			{
				tmp = *(strings + i);
				*(strings + i) = *(strings + j);
				*(strings + j) = tmp;
			}
			j++;
		}
		i++;
	}
	return (strings);
}

int strcompare(char *s1, char *s2)
{
    size_t index;

    if (NULL == s1 || NULL == s2)
        return (0);
    index = 0;
	while (*(s1 + index) || *(s2 + index))
    {
        if (*(s1 + index) == *(s2 + index))
        {
            index++;
            continue;
        }
        if ((*(s1 + index) | 32) == (*(s2 + index) | 32))
        {
            if (*(s1 + index) >= 'A' && *(s1 + index) <= 'Z' && *(s2 + index) >= 'a' && *(s2 + index) <= 'z')
                return (1);
            if (*(s1 + index) >= 'a' && *(s1 + index) <= 'z' && *(s2 + index) >= 'A' && *(s2 + index) <= 'Z')
                return (-1);
        }
        return (*(s1 + index) - *(s2 + index));
    }
	return (0);
}

int	strs_add_line(char ***strs, char *line)
{
	t_uint	size;

	if (NULL == *strs || NULL == line)
		return (FAILURE);
	size = strings_size(*strs);
	*strs = (char **)realloc(*strs, sizeof(char *) * (size + 2));
	if (NULL == *strs)
		return (FAILURE);
	*(*strs + size) = (char *)malloc(sizeof(char) * (strlen(line) + 1));
	if (NULL == *(*strs + size))
	{
		*(*strs + size + 1) = NULL;
		return (FAILURE);
	}
	strcpy(*(*strs + size), line);
	*(*strs + size + 1) = NULL;
	return (SUCCESS);
}

char	*strshuffle(char *str)
{
	size_t	len;
	char	c;
	int		index;
	int		swap_index;

	if (NULL == str)
		return (NULL);
	len = strlen(str);
	index = 0;
	while (*(str + index))
	{
		swap_index = rand() % len;
		c = *(str + index);
		*(str + index) = *(str + swap_index);
		*(str + swap_index) = c;
		index++;
	}
	return (str);
}

t_uint	strings_size(char **strings)
{
	t_uint	size;

	if (NULL == strings)
		return (0);
	size = 0;
	while (*(strings + size))
		size++;
	return (size);
}

void	free_strings(char **strs)
{
	t_uint	index;

	if (NULL == strs)
		return ;
	index = 0;
	while (*(strs + index))
	{
		free(*(strs + index));
		index++;
	}
	free(strs);
	strs = NULL;
	return ;
}
