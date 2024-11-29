#include "../headers/add.h"

int add_command(char *page, char *identifier, char *password, int overwrite)
{
    if (exist(page) && !overwrite)
    {
        error_msg("This plateform already exist");
        printf("Tap add! to overwrite\n");
        return 1;
    }
    int new_width;
    if (!overwrite)
    {
        new_width = add_pass(page, identifier, password);
    }
    else
    {
        int line = exist(page);
        if (line)
        {
            new_width = overwrite_pass(page, identifier, password, line);
        }
        else
        {
            new_width = add_pass(page, identifier, password);
        }
    }
    if (new_width < 0)
    {
        error_msg("Cannot add the password");
        return 1;
    }
    else
    {
        if (new_width > text_width)
        {
            text_width = new_width;
        }
    }
    text = sort(text);
    return 0;
}

int add_pass(char *name, char *identifier, char *password)
{
    int length = strlen(name)+strlen(identifier)+strlen(password)+strlen(separation)*2+1;

    text = (char **)realloc(text, (text_height+1) * sizeof(char *));
    if (text == NULL)
    {
        printf("realloc ?\n");
        error_msg("Memory allocation error");
        return -1;
    }
    text[text_height] = (char *)malloc(length * sizeof(char));
    if (text[text_height] == NULL)
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

    text[text_height][0] = '\0';
    strcat(text[text_height], line);
    text_height++;
    return length-1;
}

int overwrite_pass(char *name, char *identifier, char *password, int line_num)
{
    int length = strlen(name)+strlen(identifier)+strlen(password)+strlen(separation)*2+1;

    char line[length];
    line[0] = '\0';
    strcat(line, name);
    strcat(line, separation);
    strcat(line, identifier);
    strcat(line, separation);
    strcat(line, password);

    strcpy(text[line_num-1], line);
    return length-1;
}