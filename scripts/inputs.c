#include "../headers/inputs.h"

char *input(char *str, int returns)
{
    char *string;
    char c;
    int index = 0;

    string = (char *) malloc((MAX_LENGTH+1) * sizeof(char));
    if (string == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        return NULL;
    }
    
    printf("%s", str);

    while ((c = getchar()) != '\n' && index < MAX_LENGTH)
    {
        string[index] = c;
        index++;
    }
    string[index] = '\0';

    for (int i = 0; i < returns; i++)
        printf("\n");
        
    return string;
}