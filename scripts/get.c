#include "../headers/get.h"

int get_command(char *page, char **text, char *separation, int height)
{
    if (get_pass(page, text, separation, height))
    {
        return 1;
    }
    return 0;
}

int get_pass(char *name, char **text, char *separation_str, int height)
{
    int find = 0, index = 0, _index, separation_index, separation_length = strlen(separation_str);
    char *page, *identifier, *password;
    for (int line = 0; line < height; line++)
    {
        page = get_plateform_name(text[line], separation_str);
        if (page == NULL)
        {
            error_msg("Cannot get the plateform name");
            return 1;
        }
        //if the asking plateform name and the one found are the same, get the identifier and password
        if (!strcmp(name, page))
        {
            index += strlen(page) + strlen(separation_str);
            find = 1;
            //get the identifier
            identifier = (char *)malloc(strlen(text[line]) * sizeof(char));
            if (identifier == NULL)
            {
                free(page);
                error_msg("Memory allocation error");
                return 1;
            }
            _index = separation_index = 0;
            while (separation_index < separation_length && text[line][index])
            {
                if (text[line][index] == separation_str[separation_index])
                {
                    separation_index++;
                }
                else
                {
                    separation_index = 0;
                }
                identifier[_index] = text[line][index];
                index++;
                _index++;
            }
            identifier[_index-separation_length] = '\0';
            //get the password
            password = (char *)malloc(strlen(text[line]) * sizeof(char));
            if (password == NULL)
            {
                free(page);
                free(identifier);
                error_msg("Memory allocation error");
                return 1;
            }
            _index = 0;
            while (text[line][index] && text[line][index] != 10 && text[line][index] != 13)
            {
                password[_index] = text[line][index];
                _index++;
                index++;
            }
            password[_index] = '\0';
            break;
        }
        else
        {
            free(page);
        }
    }
    if (!find)
    {
        error_msg("The given name is non-exitent or incorrect");
        return 1;
    }
    //display the informations
    printf("\n > Plateform : %s\n", page);
    printf(" > Identifier : %s\n", identifier);
    printf(" > Password : %s\n\n", password);

    FILE *clipboard = popen(CLIPBOARD_CMD, "w");
    if (clipboard == NULL)
    {
        free(page);
        free(identifier);
        free(password);
        error_msg("Failed to open clipboard");
        return 1;
    }
    fprintf(clipboard, password);
    pclose(clipboard);

    printf("Password copied !\n");
    free(page);
    free(identifier);
    free(password);
    return 0;
}