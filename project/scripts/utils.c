#include "../manager.h"

int exist(char *name)
{
    for (int i = 0; i < text_height; i++)
    {
        char *plateform = get_plateform_name(text[i]);
        if (plateform == NULL)
        {
            exit(1);
        }
        if (!strcmp(plateform, name))
        {
            free(plateform);
            return i;
        }
        free(plateform);
    }
    return -1;
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

char *get_plateform_name(char *str)
{
    int index = 0, separation_index, separation_length = strlen(separation);
    char *page = (char *)malloc(sizeof(char *) * strlen(str));
    if (page == NULL)
    {
        error_msg("Memory allocation error");
        return NULL;
    }
    separation_index = 0;
    while (separation_index < separation_length && str[index])
    {
        if (str[index] == separation[separation_index])
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

int is_digit(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] < 47 || str[i] > 56)
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int power(int number, int power)
{
    if (power == 0)
    {
        return 1;
    }
    else if (power < 0)
    {
        return 0;
    }
    int result = 1;
    for (int i = 0; i < power; i++)
    {
        result *= number;
    }
    return result;
}

char *shuffle(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        int index = rand()%strlen(str);
        int _index = rand()%strlen(str);
        char save = str[index];
        str[index] = str[_index];
        str[_index] = save;
    }
    return str;
}

void error_msg(char *message)
{
    if (last_msg_is_error)
    {
        fprintf(stderr, "    Error : %s\n", message);
    }
    else
    {
        fprintf(stderr, "\n    Error : %s\n", message);
    }
    last_msg_is_error = 1;
    return;
}