#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/add.h"
#include "../headers/file.h"
#include "../headers/get.h"
#include "../headers/help.h"
#include "../headers/inputs.h"
#include "../headers/list.h"   
#include "../headers/remove.h"
#include "../headers/str.h"
#include "../headers/utils.h"

int run_command(char *_command, char ***text, char *separation, int *height, int *width, int *running, int *rewrite);

int main()
{
    char filename[] = "passwords.txt";
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        error_msg("Cannot open the file");
        return 1;
    }
    char **text = read_file(file);
    if (text == NULL)
    {
        error_msg("Cannot read the file");
        fclose(file);
        return 1;
    }
    
    char *separation = "     ", *command_line;
    int running = 1, rewrite = 0, width = get_width(file), height = get_height(file);
    fclose(file);
    text = sort(text, height);
    if (!width)
    {
        height = 0;
    }
    printf("\nTap help for more informations\n\n");
    while (running)
    {
        command_line = input("> ", 0);
        if (run_command(command_line, &text, separation, &height, &width, &running, &rewrite))
        {
            error_msg("Unknow command");
        }
        free(command_line);
    }
    if (rewrite)
    {    
        text = sort(text, height);
        FILE *end_file = fopen(filename, "w");
        if (end_file == NULL)
        {
            error_msg("Cannot open the file");
            return 1;
        }
        write_file(end_file, text, height);
        fclose(end_file);
        for (int i = 0; i < height; i++)
            free(text[i]);
    }
    free(text);
    return 0;
}

int run_command(char *_command, char ***text, char *separation, int *height, int *width, int *running, int *rewrite)
{
    int length = get_words_num(_command);
    char args[length][strlen(_command)];
    int index = 0, _index = 0, word_index = 0, is_word = 0;
    char word[strlen(_command)];
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
            list_command(*text, separation, *height);
        }
        return 0;
    }
    else if (!strcmp(args[0], "get"))
    {
        if (!(*height))
        {
            error_msg("There is no passwords you can get");
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
            get_command(args[1], *text, separation, *height);
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
            if (!add_command(args[1],args[2],args[3], text, separation, height, width, 0))
            {
                *rewrite = 1;
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
            if (!add_command(args[1],args[2],args[3], text, separation, height, width, 1))
            {
                *rewrite = 1;
            }
        }
        return 0;
    }
    else if (!strcmp(args[0], "remove") || !strcmp(args[0], "rm"))
    {
        if (!(*height))
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
            if (!remove_command(args[1], text, separation, height, width))
            {
                *rewrite = 1;
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
            *running = 0;
        }
        return 0;
    }
    return 1;
}
