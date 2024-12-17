#include "../manager.h"

int remove_command(char *page)
{
    int new_width = remove_pass(page);
    if (new_width < 0)
    {
        return 1;
    }
    else
    {
        if (!new_width)
        {
            text_width = new_width;
        }
    }
    text = sort(text);
    return 0;
}

int remove_pass(char *name)
{
    int lineword_index, find = 0;
    char *page;
    for (int line = 0; line < text_height; line++)
    {
        page = get_plateform_name(text[line]);
        if (page == NULL)
        {
            exit(1);
        }
        if (!strcmp(name, page))
        {
            free(page);
            lineword_index = line;
            find = 1;
            break;
        }
        else
        {
            free(page);
        }
    }
    if (find)
    {
        if (text_height == 1)
        {
            **text = '\0';
            text_height--;
            return 0;
        }
        if (lineword_index != text_height-1)
        {
            free(*(text+lineword_index));
            *(text+lineword_index) = *(text+text_height-1);
        }
        text_height--;
        text = realloc(text, text_height * sizeof(char *));
        if (text == NULL)
        {
            error_msg("Memory allocation error");
            return -1;
        }
    }
    else
    {
        error_msg("The given name is non-exitent or incorrect");
        return -1;
    }
    return text_width;
}
