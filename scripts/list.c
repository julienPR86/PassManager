#include "../manager.h"

int list_command()
{
    if (!text_height)
    {
        error_msg("There is no passwords to list");
        return 1;
    }
    char *page;
    printf("\n");
    for (int line = 0; line < text_height; line++)
    {
        page = get_plateform_name(text[line]);
        if (page == NULL)
        {
            return 1;
        }
        printf(" > %s\n", page);
        free(page);
    }
    printf("\n");
    return 0;
}
