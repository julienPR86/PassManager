#include "../manager.h"

const char *separation = "     ";
const char *data_path = "passwords.txt";
int last_msg_is_error = 0;
int is_modifiable = 0;
int running = 1;
int text_height = 0;
int text_width = 0;
char **text = NULL;
int rewrite = 0;

int init()
{
    FILE *file = fopen(data_path, "rb");
    if (file == NULL)
    {
        error_msg("File not found");
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
    is_modifiable = 1;
    return 0;
}