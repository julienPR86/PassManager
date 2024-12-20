#include "../manager.h"

char *input(char *str, int returns)
{
    char *string;
    char c;
    int index = 0;

    string = (char *)malloc((MAX_LENGTH+1) * sizeof(char));
    if (string == NULL)
    {
        error_msg("Memory allocation error");
        return NULL;
    }
    
    if (last_msg_is_error)
    {
        printf("\n%s", str);
    }
    else
    {
        printf("%s", str);
    }
    

    while ((c = getchar()) != '\n' && index < MAX_LENGTH)
    {
        if (c == '&' || c == '$' || c == ';')
        {
            empty_stdin();
            error_msg("Forbidden character in input");
            free(string);
            return NULL;
        }
        string[index] = c;
        index++;
    }
    string[index] = '\0';

    for (int i = 0; i < returns; i++)
        printf("\n");
    
    if (index >= MAX_LENGTH)
    {
        empty_stdin();
    }
        
    return string;
}

void empty_stdin()
{
    while (getchar() != '\n');
    return;
}