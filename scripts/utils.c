#include "../headers/utils.h"

int exist(char **text, char *name, char *separation_str, int height)
{
    for (int i = 0; i < height; i++)
    {
        char *plateform = get_plateform_name(text[i], separation_str);
        if (plateform == NULL)
        {
            exit(1);
        }
        if (!strcmp(plateform, name))
        {
            free(plateform);
            return i+1;
        }
        free(plateform);
    }
    return 0;
}

int get_words_num(char *string)
{
    int words = 0, index = 0, is_word = 0;
    while (string[index])
    {
        if (string[index] >= 33 && string[index] <= 126)
        {
            is_word = 1;
        }
        else if (string[index] == ' ')
        {
            if (is_word)
            {
                words++;
                is_word = 0;
            }
        }
        if (string[index+1] == '\0')
        {
            if (is_word)
            {
                words++;
            }
        }
        index++;
    }
    return words;
}

char *get_plateform_name(char *str, char *separation_str)
{
    int index = 0, separation_index, separation_length = strlen(separation_str);
    char *page = (char *)malloc(sizeof(char *) * strlen(str));
    if (page == NULL)
    {
        error_msg("Memory allocation error");
        return NULL;
    }
    separation_index = 0;
    while (separation_index < separation_length && str[index])
    {
        if (str[index] == separation_str[separation_index])
        {
            separation_index++;
        }
        else
        {
            separation_index = 0;
        }
        page[index] = str[index];
        index++;
    }
    page[index-separation_length] = '\0';
    return page;
}

int error_msg(char *message)
{
    fprintf(stderr, "\n    Error : %s\n\n", message);
    return 0;
}