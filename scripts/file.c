#include "../headers/file.h"

char **read_file(FILE *file)
{
    int height = get_height(file);
    int width = get_width(file);
    char **text = (char **)malloc(sizeof(char *) * height);
    if (text == NULL)
    {
        error_msg("Memory allocation error");
        return NULL;
    }
    if (width)
    {
        for (int i = 0; i < height; i++)
        {
            text[i] = (char *)malloc(sizeof(char) * width);
            if (text[i] == NULL)
            {
                error_msg("Memory allocation error");
                for (int j = 0; j < i; j++)
                    free(text[j]);
                free(text);
                return NULL;
            }
        }
    }
    else
    {
        return text;
    }
    int column = 0, line = 0;
    char c;
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n' || c == '\r')
        {
            text[line][column] = '\0';
            line++;
            column = 0;
            if (c == '\r' && (c = fgetc(file)) != '\n')
                ungetc(c, file);
        }
        else
        {
            text[line][column] = c;
            column++;
        }
    }
    text[line][column] = '\0';
    rewind(file);
    return text;
}

int get_height(FILE *file)
{
    int lines = 1;
    char c;
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
            lines++;
    }
    rewind(file);
    return lines;
}

int get_width(FILE *file)
{
    int width = 0;
    int max_width = 0;
    char c;
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
        {
            if (width > max_width)
                max_width = width;
            width = 0;
            continue;
        }
        width++;
    }
    if (width > max_width)
        max_width = width;
    rewind(file);
    return max_width;
}

int write_file(FILE *file, char **text, int height)
{
    for (int i = 0; i < height; i++)
    {
        if (i != height-1)
            fprintf(file, "%s\n", text[i]);
        else
            fprintf(file, "%s", text[i]);
    }
    return 0;
}