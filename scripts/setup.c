#include "../headers/setup.h"

separation = "     ";
filename = "passwords.txt";
running = 1;
text_height = 0;
text_width = 0;
text = NULL;

int init(void)
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
    return 0;
}