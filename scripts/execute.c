#include "../manager.h"

int run_command(char *_command)
{
    int length = get_words_num(_command);
    char args[length][strlen(_command)+1];
    int index = 0, _index = 0, word_index = 0, is_word = 0;
    char word[strlen(_command)+1];
    while (_command[index])
    {
        if (_command[index] >= 33 && _command[index] <= 126)
        {
            word[word_index] = _command[index];
            is_word = 1;
            word_index++;
        }
        else if (_command[index] == ' ')
        {
            if (is_word)
            {
                word[word_index] = '\0';
                strcpy(args[_index], word);
                _index++;
                is_word = 0;
                word_index = 0;
            }
        }
        else
        {
            error_msg("Name standard isn't respected");
            return 0;
        }
        if (_command[index+1] == '\0')
        {
            if (is_word)
            {
                word[word_index] = '\0';
                strcpy(args[_index], word);
            }
        }
        index++;
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
            get_command(args[1]);
        }
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
        return 0;
    }
    else if (!strcmp(args[0], "help") || !strcmp(args[0], "?"))
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
        return 0;
    }
    return 1;
}
