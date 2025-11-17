#include "../headers/manager.h"

t_Pass	*get_pass(char *name)
{
	t_Pass	*pass;
	int	index;

	if (NULL == name)
		return (NULL);
	index = get_pass_index(data_file_content, name);
	if (index < 0 || NULL == *(data_file_content + index))
		return (NULL);
	pass = (t_Pass *)malloc(sizeof(t_Pass));
	if (NULL == pass)
		return (NULL);
	pass->name = get_word(*(data_file_content + index), 0, "\t ");
	pass->identifier = get_word(*(data_file_content + index), 1, "\t ");
	pass->password = get_word(*(data_file_content + index), 2, "\t ");
	return (pass);
}

int	get_pass_index(char **content, char *name)
{
	char	*word;
	int		index;

	if (NULL == data_file_content || NULL == content || NULL == name)
		return (-1);
	index = 0;
	word = get_word(*(data_file_content + index), 0, "\t ");
	while (*(content + index) && strcmp(word, name))
	{
		free(word);
		index++;
		word = get_word(*(data_file_content + index), 0, "\t ");
	}
	free(word);
	if (NULL == *(content + index))
		return (-1);
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