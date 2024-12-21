#include "../manager.h"

int data_command(int action, char *arg)
{
    switch (action)
    {
        case 0:
            passwords_file_path_print();
            break;
        case 1:
            if(passwords_file_path_change(arg))
            {
                return 1;
            }
            break;
        default:
            return 1;
    }
    return 0;
}

int passwords_file_path_change(char *path)
{
    return 0;
}

void passwords_file_path_print()
{
    if (!strlen(passwords_file_path))
    {
        error_msg("There is no provided path");
    }
    else
    {
        printf("\n > Path : %s\n\n", passwords_file_path);
    }
    return;
}