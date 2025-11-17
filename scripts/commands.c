#include "../headers/manager.h"

t_Command	sub_data_cmd_change = {"change", {}, 1, 1, NULL, {}};

t_Command	commands[COMMAND_COUNT] = 
{
	{"list", {"ls"}, 0, 0, &list_cmd, {}},
	{"get", {}, 1, 1, &get_cmd, {}},
	{"add", {}, 3, 3, &add_cmd, {}},
	{"replace", {}, 4, 4, &replace_cmd, {}},
	{"remove", {"rm"}, 1, 1, &remove_cmd, {}},
	{"data", {}, 0, 1, &data_cmd, {&sub_data_cmd_change}},
	{"help", {"man"}, 0, 1, &help_cmd, {}},
	{"exit", {"quit"}, 0, 0, &exit_cmd, {}},
};

int	list_cmd(char **args)
{
	char	*word;
	t_uint	index;

	if (NULL == data_file_content)
		return (FAILURE);
	(void)args;
	index = 0;
	while (*(data_file_content + index))
	{
		word = get_word(*(data_file_content + index), 0, "\t ");
		printf("\t%u : %s\n", index + 1, word);
		free(word);
		index++;
	}
	if (index == 0)
		return (DATABASE_EMPTY);
	return (SUCCESS);
}

int	get_cmd(char **args)
{
	int		index;
	t_Pass	*pass;

	if (NULL == args || NULL == data_file_content)
		return (FAILURE);
	index = get_pass_index(data_file_content, *args);
	if (index < 0)
		return (DATABASE_EMPTY);
	pass = get_pass(*args);
	if (NULL == pass)
		return (ENTRY_NOT_FOUND);
	display_pass(pass);
	free_pass(pass);
	return (SUCCESS);
}

int	add_cmd(char **args)
{
	t_uint	size;
	int		index;

	if (NULL == args || NULL == data_file_content)
		return (FAILURE);
	index = get_pass_index(data_file_content, *args);
	if (index >= 0)
		return (ENTRY_ALREADY_EXISTS);
	size = strings_size(data_file_content);
	data_file_content = (char **)realloc(data_file_content, sizeof(char *) * (size + 2));
	if (NULL == data_file_content)
		return (FAILURE);
	*(data_file_content + size) = (char *)malloc(sizeof(char) * (strlen(*args) + strlen(*(args + 1)) + strlen(*(args + 2)) + 3));
	if (NULL == *(data_file_content + size))
	{
		data_file_content = (char **)realloc(data_file_content, size);
		if (NULL == data_file_content)
			return (FAILURE);
		return (FAILURE);
	}
	*(*(data_file_content + size)) = '\0';
	strcat(*(data_file_content + size), *args);
	strcat(*(data_file_content + size), " ");
	strcat(*(data_file_content + size), *(args + 1));
	strcat(*(data_file_content + size), " ");
	strcat(*(data_file_content + size), *(args + 2));
	*(data_file_content + size + 1) = NULL;
	rewrite_data_file = 1;
	return (SUCCESS);
}

int	replace_cmd(char **args)
{
	int	index;

	if (NULL == args || NULL == data_file_content)
		return (FAILURE);
	index = get_pass_index(data_file_content, *args);
	if (index >= 0 && strcmp(*args, *(args + 1)))
		return (ENTRY_ALREADY_EXISTS);
	if (ENTRY_NOT_FOUND == remove_cmd(args))
		return (ENTRY_NOT_FOUND);
	add_cmd(args + 1);
	return (SUCCESS);
}

int	remove_cmd(char **args)
{
	char	*tmp;
	t_uint	size;
	int		rm_index;
	
	if (NULL == args || NULL == data_file_content)
		return (FAILURE);
	size = strings_size(data_file_content);
	rm_index = get_pass_index(data_file_content, *args);
	if (rm_index < 0)
		return (ENTRY_NOT_FOUND);
	tmp = *(data_file_content + size - 1);
	*(data_file_content + size - 1) = *(data_file_content + rm_index);
	*(data_file_content + rm_index) = tmp;
	data_file_content = (char **)realloc(data_file_content, sizeof(char *) * size);
	if (NULL == data_file_content)
		return (FAILURE);
	free(*(data_file_content + size - 1));
	*(data_file_content + size - 1) = NULL;
	rewrite_data_file = 1;
	return (SUCCESS);
}

int	data_cmd(char **args)
{
	char	*data_path;

	if (NULL == args)
		return (FAILURE);
	if (NULL == *args)
	{
		data_path = get_setting("data_path");
		message_output(data_path);
		message_output("\n");
		free(data_path);
		return (SUCCESS);
	}
	return (SUCCESS);
}

int	help_cmd(char **args)
{
	FILE	*help_file;
	char	*cmd_name;
	char	**help_content;
	char	help_file_name[MAX_STRING_LENGTH + 24] = "data/commands/help/commands.txt";
	t_uint	index;

	if (NULL == args)
		return (FAILURE);
	if (*args)
	{
		cmd_name = get_cmd_name(*args);
		if (NULL == cmd_name)
			return (HELP_ENTRY_NOT_FOUND);
		help_file_name[19] = '\0';
		strncat(help_file_name, cmd_name, 256);
		strncat(help_file_name, ".txt", 5);
	}
	help_file = fopen(help_file_name, "r");
	if (NULL == help_file)
		return (COULD_NOT_OPEN_FILE);
	index = 0;
	help_content = read_file(help_file);
	while (*(help_content + index))
	{
		printf("%s\n", *(help_content + index));
		index++;
	}
	free_strings(help_content);
	fclose(help_file);
	return (SUCCESS);
}

int	exit_cmd(char **args)
{
	(void)args;
	return (EXIT_PROGRAM);
}
