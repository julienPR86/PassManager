#include <stdio.h>
#include <stdlib.h>
#include "headers/file.h"
#include "headers/manager.h"
#include "headers/str.h"
#include "headers/utils.h"

int main(void)
{
    char filename[] = "passwords.txt";
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        error_msg("Cannot open the file");
        return 1;
    }
    char **text = read_file(file);
    if (text == NULL)
    {
        error_msg("Cannot read the file");
        fclose(file);
        return 1;
    }
    
    char *separation = "     ", *command_line;
    int running = 1, rewrite = 0, width = get_width(file), height = get_height(file);
    fclose(file);
    text = sort(text, height);
    if (!width)
    {
        height = 0;
    }
    printf("\nTap help for more informations\n\n");
    while (running)
    {
        command_line = input("> ", 0);
        if (run_command(command_line, &text, separation, &height, &width, &running, &rewrite))
        {
            error_msg("Unknow command");
        }
        free(command_line);
    }
    if (rewrite)
    {    
        text = sort(text, height);
        FILE *end_file = fopen(filename, "w");
        if (end_file == NULL)
        {
            error_msg("Cannot open the file");
            return 1;
        }
        write_file(end_file, text, height);
        fclose(end_file);
        for (int i = 0; i < height; i++)
            free(text[i]);
    }
    free(text);
    return 0;
}