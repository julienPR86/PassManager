#include <stdio.h>
#include <stdlib.h>

char *input(char *text, int returns)
{
    char *string;
    char c;
    int lenght = 512, index = 0;

    string = (char *) malloc((lenght+1) * sizeof(char));
    if (string == NULL)
    {
        fprintf(stderr, "Memory allocation error\n");
        exit(1);
    }
    
    printf(text);

    while ((c = getchar()) != '\n' && index < lenght)
    {
        string[index] = c;
        index++;
    }
    string[index] = '\0';
    for (int i = 0; i < returns; i++)
        printf("\n");
    return string;
}