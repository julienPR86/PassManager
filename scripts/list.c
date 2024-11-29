#include "../headers/list.h"

int list_command(char **text, char *separation_str, int height)
{
    if (!height)
    {
        error_msg("There is no passwords to list");
        return 1;
    }
    char *page;
    printf("\n");
    for (int line = 0; line < height; line++)
    {
        page = get_plateform_name(text[line], separation_str);
        if (page == NULL)
        {
            exit(1);
        }
        printf(" > %s\n", page);
        free(page);
    }
    printf("\n");
    return 0;
}