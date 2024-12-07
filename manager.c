#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manager.h"

int main(void)
{
    if (init())
    {
        error_msg("Could not init the variables\n");
        return 1;
    }
    if (!text_width)
    {
        text_height = 0;
    }
    char *command_line;
    int rewrite = 0;
    printf("\nTap help for more informations\n\n");
    while (running)
    {
        command_line = input("> ", 0);
        if (run_command(command_line, &rewrite))
        {
            error_msg("Unknow command");
        }
        free(command_line);
    }
    if (rewrite)
    {    
        text = sort(text);
        FILE *end_file = fopen(filename, "w");
        if (end_file == NULL)
        {
            error_msg("Cannot open the file");
            return 1;
        }
        write_file(end_file);
        fclose(end_file);
        for (int i = 0; i < text_height; i++)
            free(text[i]);
    }
    free(text);
    return 0;
}
