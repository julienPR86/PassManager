#include "../manager.h"

const char *separation = "     ";
const char *filename = "passwords.txt";
int running = 1;
int text_height = 0;
int text_width = 0;
char **text = NULL;
int rewrite = 0;

int init()
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        error_msg("Cannot open the file");
        return 1;
    }
    get_dimensions(file, &text_height, &text_width);
    text = read_file(file);
    if (text == NULL)
    {
        error_msg("Cannot read the file");
        fclose(file);
        return 1;
    }
    fclose(file);
    return 0;
}