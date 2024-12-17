#include "../manager.h"

char **read_file(FILE *file)
{
    char **text = (char **)malloc(sizeof(char *) * text_height);
    if (text == NULL)
    {
        error_msg("Memory allocation error");
        return NULL;
    }
    if (!text_height)
    {
        return text;
    }
    for (int i = 0; i < text_height; i++)
    {
        text[i] = (char *)malloc(sizeof(char) * text_height);
        if (text[i] == NULL)
        {
            error_msg("Memory allocation error");
            for (int j = 0; j < i; j++)
            {
                    free(text[j]);
            }
            free(text);
            return NULL;
        }
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
            {
                ungetc(c, file);
            }
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
        {
            lines++;
        }
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
            {
                max_width = width;
            }
            width = 0;
            continue;
        }
        width++;
    }
    if (width > max_width)
    {
        max_width = width;
    }
    rewind(file);
    return max_width;
}

int write_file()
{
    text = sort(text);
    FILE *file = fopen(filename, "w");
    if (NULL == file)
    {
        error_msg("Cannot open the file");
        return 1;
    }
    for (int i = 0; i < text_height; i++)
    {
        if (i == text_height-1)
        {
            fprintf(file, "%s", text[i]);
            break;
        }
        fprintf(file, "%s\n", text[i]);
    }
    fclose(file);
    return 0;
}
