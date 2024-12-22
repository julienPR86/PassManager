#include "../manager.h"

char *gen_password(int length)
{
    const int numbers[] = {0,1,2,3,4,5,6,7,8,9};
    const char lower_characters[] = "abcdefghijklmnopqrstuvwxyz";
    const char upper_character[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const char specials[] = "!#$&()*-/:;<>=?@[]_^";

    char *password = (char *)malloc(sizeof(char) * (length+1));
    int i, index = 0;
    for (i = 0; i < length/4; i++)
    {
        password[index] = specials[rand()%strlen(specials)];
        index++;
    }
    for (i = 0; i < length/4; i++)
    {
        password[index] = numbers[rand()%(sizeof(numbers)/sizeof(int))]+'0';
        index++;
    }
    for (i = 0; i < length/4; i++)
    {
        password[index] = upper_character[rand()%strlen(upper_character)];
        index++;
    }
    
    for (i = 0; i < (length/4)+(length%4); i++)
    {
        password[index] = lower_characters[rand()%strlen(lower_characters)];
        index++;
    }
    password[index] = '\0';
    password = shuffle(password);
    return password;
}

