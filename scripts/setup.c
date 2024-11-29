#include "../headers/setup.h"

int init(void)
{
    separation = "     ";
    filename = "passwords.txt";
    running = 1;
    
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
    return 0;
}