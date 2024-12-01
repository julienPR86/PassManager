#include "../main.h"

const char *separation = "     ";
const char *filename = "passwords.txt";
int running = 1;
int text_height = 0;
int text_width = 0;
char **text = NULL;

int init()
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