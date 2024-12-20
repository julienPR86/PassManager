#include "../manager.h"

char **read_file(FILE *file, int height, int width)
{
    char **text = (char **)malloc(sizeof(char *) * height);
    if (text == NULL)
    {
        error_msg("Memory allocation error");
        return NULL;
    }
    if (!height)
    {
        return text;
    }
    for (int i = 0; i < height; i++)
    {
        text[i] = (char *)malloc(sizeof(char) * width);
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

void get_dimensions(FILE *file, int *h, int *w)
{
    int lines = 1, width = 0, max_width = 0;
    char c;
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n')
        {
            lines++;
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
    if (NULL != h){*h = lines;}
    if (NULL != w){*w = max_width;}
    rewind(file);
    return;
}

int write_file(char *name, int h)
{
    text = sort(text);
    FILE *file = fopen(name, "w");
    if (NULL == file)
    {
        error_msg("Cannot open the file");
        return 1;
    }
    for (int i = 0; i < h; i++)
    {
        if (i == h-1)
        {
            fprintf(file, "%s", text[i]);
            break;
        }
        fprintf(file, "%s\n", text[i]);
    }
    fclose(file);
    return 0;
}
