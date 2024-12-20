#include "manager.h"

int main(void)
{
    if (init())
    {
        error_msg("Could not init the variables\n");
        printf("Tap help for more informations\n\n");
    }
    else
    {
        printf("\nTap help for more informations\n\n");
    }
    if (!text_width)
    {
        text_height = 0;
    }
    char *command_line;        
    while (running)
    {
        command_line = input("> ", 0);
        last_msg_is_error = 0;
        if (NULL != command_line)
        {
            if (run_command(command_line))
            {
                error_msg("Unknow command");
            }
            free(command_line);
        }
    }
    if (rewrite)
    {    
        if (write_file())
        {
            error_msg("Could not write in the file");
        }
    }
    for (int i = 0; i < text_height; i++)
    {
        free(text[i]);
    }
    free(text);
    printf("exit ok\n");
    return 0;
}
