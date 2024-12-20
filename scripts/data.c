#include "../manager.h"

int data_path_change(char *path)
{
    return 0;
}

void data_path_print()
{
    if (!strlen(data_path))
    {
        error_msg("There is no provided path");
    }
    else
    {
        printf("\n > Path : %s\n\n", data_path);
    }
    return;
}