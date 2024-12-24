#include "../manager.h"

int add_command(char *page, char *identifier, char *password, int overwrite)
{
    if (!(exist(page) < 0) && !overwrite)
    {
        error_msg("This plateform already exist");
        printf("Tap add! to overwrite\n");
        return 1;
    }

    if (!strcmp(password, "rand"))
    {
        password = gen_password(12);
    }

    if (!overwrite)
    {
        if (add_pass(page, identifier, password) < 0)
        {
            error_msg("Could not add the password");
            return 1;
        }
    }
    else
    {
        int line = exist(page);
        if (!(line < 0))
        {
            overwrite_pass(page, identifier, password, line);
        }
        else
        {
            if (add_pass(page, identifier, password) < 0)
            {
                error_msg("Could not add the password");
                return 1;
            }
        }
    }
    free(password);
    text = sort(text);
    return 0;
}

int add_pass(char *name, char *identifier, char *password)
{
    int length = strlen(name)+strlen(identifier)+strlen(password)+strlen(separation)*2+1;

    text = (char **)realloc(text, (text_height+1) * sizeof(char *));
    if (text == NULL)
    {
        error_msg("Memory allocation error");
        return -1;
    }
    text[text_height] = (char *)malloc(length * sizeof(char));
    if (text[text_height] == NULL)
    {
        free(text[text_height]);
        error_msg("Memory allocation error");
        return -1;
    }

    char line[length];
    line[0] = '\0';
    char *args[] = {name, (char *)separation, identifier, (char *)separation, password};
    string(line, args, 5);

    text[text_height][0] = '\0';
    strcat(text[text_height], line);
    text_height++;
    if (length > text_width)
    {
        text_width = length;
    }
    return 0;
}

int overwrite_pass(char *name, char *identifier, char *password, int line_index)
{
    int length = strlen(name)+strlen(identifier)+strlen(password)+strlen(separation)*2+1;

    char line[length];
    line[0] = '\0';
    char *args[] = {name, (char *)separation, identifier, (char *)separation, password};
    string(line, args, 5);
    strcpy(text[line_index], line);
    if (length > text_width)
    {
        text_width = length;
    }
    return 0;
}
