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

char	*get_cmd_name(char *alias)
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
			if (*((*(commands + index))->alias + alias_index) && !strcmp(alias, *((*(commands + index))->alias + alias_index)))
				return ((*(commands + index))->name);
			alias_index++;
		}
		if (!strcmp(alias, (*(commands + index))->name))
			return ((*(commands + index))->name);
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
			if (strcmp(*(strings + i), *(strings + j)) > 0)
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
