#include "../headers/manager.h"

t_Pass	*get_pass(char *name)
{
	t_Pass	*pass;
	t_uint	size;
	t_uint	index;

	if (NULL == name)
		return (NULL);
	size = strings_size(data_file_content);
	index = get_pass_index(data_file_content, name);
	if (NULL == *(data_file_content + index) || index >= size)
		return (NULL);
	pass = (t_Pass *)malloc(sizeof(t_Pass));
	if (NULL == pass)
		return (NULL);
	pass->name = get_word(*(data_file_content + index), 0);
	pass->identifier = get_word(*(data_file_content + index), 1);
	pass->password = get_word(*(data_file_content + index), 2);
	return (pass);
}

t_uint	get_pass_index(char **content, char *name)
{
	char	*word;
	t_uint	index;

	if (NULL == content || NULL == name)
		return (0);
	index = 0;
	word = get_word(*(data_file_content + index), 0);
	while (*(content + index) && strcmp(word, name))
	{
		free(word);
		index++;
		word = get_word(*(data_file_content + index), 0);
	}
	free(word);
	return (index);
}

void	display_pass(t_Pass *pass)
{
	if (NULL == pass)
		return ;
	printf("\tName :       %s\n\tIdentifier : %s\n\tPassword :   %s\n", pass->name, pass->identifier, pass->password);
	return ;
}

void	free_pass(t_Pass *pass)
{
	if (NULL == pass)
		return ;
	free(pass->name);
	free(pass->identifier);
	free(pass->password);
	free(pass);
	pass = NULL;
	return ;
}