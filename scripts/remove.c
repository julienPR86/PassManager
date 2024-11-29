#include "../headers/remove.h"

int remove_command(char *page, char ***text, char *separation, int *height, int *width)
{
    int new_width = remove_pass(page, text, separation, height, *width);
    if (new_width < 0)
    {
        return 1;
    }
    else
    {
        if (!new_width)
        {
        *width = new_width;
        }
    }
    (*text) = sort(*text, *height);
    return 0;
}

int remove_pass(char *name, char ***text, char *separation_str, int *height, int width)
{
    int lineword_index, find = 0;
    char *page;
    for (int line = 0; line < *height; line++)
    {
        page = get_plateform_name(((*text)[line]), separation_str);
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
        if (*height == 1)
        {
            ***text = '\0';
            (*height)--;
            return 0;
        }
        if (lineword_index != (*height)-1)
        {
            free(*((*text)+lineword_index));
            *((*text)+lineword_index) = *((*text)+(*height-1));
        }
        (*height)--;
        *text = realloc(*text, (*height) * sizeof(char *));
        if (*text == NULL)
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
    return width;
}