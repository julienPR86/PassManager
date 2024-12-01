#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

const char *separation = "     ";
const char *filename = "passwords.txt";
int running = 1;
int text_height = 0;
int text_width = 0;
char **text = NULL;

int main(void)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        error_msg("Cannot open the file");
        return 1;
    }
    text = read_file(file);
    text_height = get_height(file);
    text_width = get_width(file);
    if (text == NULL)
    {
        error_msg("Cannot read the file");
        fclose(file);
        return 1;
    }
    fclose(file);
    text = sort(text);
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
