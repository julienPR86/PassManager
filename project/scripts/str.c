#include "../manager.h"

int charcmp(char chr1, char chr2, int value1, int value2)
{
    if (chr1+value1 < chr2+value2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    return 0;
}

int str_sort(char *str1, char *str2)
{
    int index = 0, _index = 0;
    while (str1[index] || str2[_index])
    {
        if (str1[index] == str2[_index])
        {
            if (str1[index]){index++;}
            if (str2[_index]){_index++;}
        }
        else
        {
            if ((str1[index] >= 65 && str1[index] <= 90) && (str2[index] >= 65 && str2[index] <= 90))
            {
                return charcmp(str1[index], str2[index], 0, 0);
            }
            else if ((str1[index] >= 65 && str1[index] <= 90) && !(str2[index] >= 65 && str2[index] <= 90))
            {
                if (str1[index]+32 == str2[_index])
                {
                    return 0;
                }
                else
                {
                    return charcmp(str1[index], str2[index], 32, 0);
                }
            }
            else if (!(str1[index] >= 65 && str1[index] <= 90) && (str2[index] >= 65 && str2[index] <= 90))
            {
                if (str1[index] == str2[_index]+32)
                {
                    return 1;
                }
                else
                {
                    return charcmp(str1[index], str2[index], 0, 32);
                }
            }
            else
            {
                return charcmp(str1[index], str2[index], 0, 0);
            }
        }
    }
    if (index < _index)
    {
        return 1;
    }
    else if (_index > index)
    {
        return 0;
    }
    return 0;
}

char **sort(char **text)
{
    if (!text_height || text_height == 1)
    {
        return text;
    }
    for (int i = 0; i < text_height; i++)
    {
        for (int j = 0; j < text_height-1; j++)
        {
            if (!str_sort(text[j], text[j+1]))
            {
                char *save = text[j];
                text[j] = text[j+1];
                text[j+1] = save;
            }
        }
    }
    return text;
}

int str_to_int(char *str)
{
    if (!is_digit(str))
    {
        error_msg("Could not convert to int");
        return -1;
    }
    int result = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        result += (str[i]-'0')*power(10, strlen(str)-i-1);
    }
    return result;
}

char *string(char *source, char **args, int args_length)
{
    for (int i = 0; i < args_length; i++)
    {
        strcat(source, args[i]);
    }
    return source;
}

