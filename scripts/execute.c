#include "../manager.h"

int run_command(char *command)
{
    int length = get_words_num(command);
    char **args = get_args(command);
    if (NULL == args)
    {
        return 0;
    }
    if (!strcmp(args[0], "help") || !strcmp(args[0], "?"))
    {
        if (length > 2)
        {
            error_msg("Too much arguments");
        }
        else
        {
            if (length == 2)
            {
                help(args[1]);
            }
            else
            {
                help(NULL);
            }
        }
        free_args(args, length);
        return 0;
    }
    else if (!strcmp(args[0], "exit") || !strcmp(args[0], "quit"))
    {
        if (length > 1)
        {
            error_msg("Too much arguments");
        }
        else
        {
            running = 0;
        }
        free_args(args, length);
        return 0;
    }
    else if (!strcmp(args[0], "data-path"))
    {
        if (length > 1)
        {
            error_msg("Too much arguments");
        }
        else
        {
            data_path_print();
        }
        free_args(args, length);
        return 0;
    }
    else if (!strcmp(args[0], "data-path-change"))
    {
        if (length > 2)
        {
            error_msg("Too much arguments");
        }
        else if (length < 2)
        {
            error_msg("not enough arguments");
        }
        else
        {
            if (data_path_change(args[1]));
            {
                error_msg("Could not change data-path");
            }
        }
        free_args(args, length);
        return 0;
    }
    if (!is_modifiable)
    {
        error_msg("Cannot access the data due to variable's non-initialisation");
        return 0;
    }
    if (!strcmp(args[0], "list") || !strcmp(args[0], "ls"))
    {
        if (length > 1)
        {
            error_msg("Too much arguments");
        }
        else
        {
            list_command();
        }
        free_args(args, length);
        return 0;
    }
    else if (!strcmp(args[0], "get"))
    {
        if (!text_height)
        {
            error_msg("There is no passwords to get");
        }
        else if (length > 2)
        {
            error_msg("Too much arguments");
        }
        else if (length < 2)
        {
            error_msg("Not enough arguments");
        }
        else
        {
            get_pass(args[1]);
        }
        free_args(args, length);
        return 0;
    }
    else if (!strcmp(args[0], "add"))
    {
        if (length > 4)
        {
            error_msg("Too much arguments");
        }
        else if (length < 4)
        {
            error_msg("Not enough arguments");
        }
        else
        {
            if (!add_command(args[1],args[2],args[3], 0))
            {
                rewrite = 1;
            }
        }
        free_args(args, length);
        return 0;
    }
    else if (!strcmp(args[0], "add!"))
    {
        if (length > 4)
        {
            error_msg("Too much arguments");
        }
        else if (length < 4)
        {
            error_msg("Not enough arguments");
        }
        else
        {
            if (!add_command(args[1],args[2],args[3], 1))
            {
                rewrite = 1;
            }
        }
        free_args(args, length);
        return 0;
    }
    else if (!strcmp(args[0], "remove") || !strcmp(args[0], "rm"))
    {
        if (!text_height)
        {
            error_msg("There is no passwords to remove");
        }
        else if (length > 2)
        {
            error_msg("Too much arguments");
        }
        else if (length < 2)
        {
            error_msg("Not enough arguments");
        }
        else
        {
            if (!remove_command(args[1]))
            {
                rewrite = 1;
            }
        }
        free_args(args, length);
        return 0;
    }
    free_args(args, length);
    return 1;
}

char **get_args(char *command)
{
    char **args = (char **)malloc(get_words_num(command) * sizeof(char *));
    if (NULL == args)
    {
        error_msg("Memory allocation error");
        return NULL;
    }
    for (int i = 0; i < get_words_num(command); i++)
    {
        args[i] = (char *)malloc(strlen(command) * sizeof(char));
        if (NULL == args[i])
        {
            free_args(args, i);
            return NULL;
        }
    }
    int command_index = 0, args_index = 0, word_index = 0, is_word = 0;
    char word[strlen(command)+1];
    while (command[command_index])
    {
        if (command[command_index] >= 33 && command[command_index] <= 126)
        {
            word[word_index] = command[command_index];
            is_word = 1;
            word_index++;
        }
        else if (command[command_index] == ' ')
        {
            if (is_word)
            {
                word[word_index] = '\0';
                strcpy(args[args_index], word);
                args_index++;
                is_word = 0;
                word_index = 0;
            }
        }
        else
        {
            error_msg("Name standard isn't respected");
            return NULL;
        }
        if (command[command_index+1] == '\0')
        {
            if (is_word)
            {
                word[word_index] = '\0';
                strcpy(args[args_index], word);
            }
        }
        command_index++;
    }
    return args;
}

void free_args(char **args, int length)
{
    for (int i = 0; i < length; i++)
    {
        free(args[i]);
    }
    free(args);
}
