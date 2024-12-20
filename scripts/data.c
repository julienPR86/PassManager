#include "../manager.h"

int data_command(int action, char *arg)
{
    switch (action)
    {
        case 0:
            data_path_print();
            break;
        case 1:
            if(data_path_change(arg))
            {
                return 1;
            }
            break;
        default:
            return 1;
    }
    return 0;
}

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