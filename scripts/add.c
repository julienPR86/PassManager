#include "../headers/add.h"

int add_command(char *page, char *identifier, char *password, char ***text, char *separation, int *height, int *width, int overwrite)
{
    if (exist(*text, page, separation, *height) && !overwrite)
    {
        error_msg("This plateform already exist");
        printf("Tap add! to overwrite\n");
        return 1;
    }
    int new_width;
    if (!overwrite)
    {
        new_width = add_pass(page, identifier, password, text, separation, height);
    }
    else
    {
        int line = exist(*text, page, separation, *height);
        if (line)
        {
            new_width = overwrite_pass(page, identifier, password, text, separation, line);
        }
        else
        {
            new_width = add_pass(page, identifier, password, text, separation, height);
        }
    }
    if (new_width < 0)
    {
        error_msg("Cannot add the password");
        return 1;
    }
    else
    {
        if (new_width > *width)
        {
            *width = new_width;
        }
    }
    (*text) = sort(*text, *height);
    return 0;
}

int add_pass(char *name, char *identifier, char *password, char ***text, char *separation, int *height)
{
    int length = strlen(name)+strlen(identifier)+strlen(password)+strlen(separation)*2+1;

    *text = (char **)realloc(*text, ((*height)+1) * sizeof(char *));
    if (*text == NULL)
    {
        printf("realloc ?\n");
        error_msg("Memory allocation error");
        return -1;
    }
    (*text)[*height] = (char *)malloc(length * sizeof(char));
    if ((*text)[*height] == NULL)
    {
        error_msg("Memory allocation error");
        return -1;
    }

    char line[length];
    line[0] = '\0';
    strcat(line, name);
    strcat(line, separation);
    strcat(line, identifier);
    strcat(line, separation);
    strcat(line, password);

    (*text)[*height][0] = '\0';
    strcat((*text)[*height], line);
    (*height)++;
    return length-1;
}

int overwrite_pass(char *name, char *identifier, char *password, char ***text, char *separation, int line_num)
{
    int length = strlen(name)+strlen(identifier)+strlen(password)+strlen(separation)*2+1;

    char line[length];
    line[0] = '\0';
    strcat(line, name);
    strcat(line, separation);
    strcat(line, identifier);
    strcat(line, separation);
    strcat(line, password);

    strcpy((*text)[line_num-1], line);
    return length-1;
}