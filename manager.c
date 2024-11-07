#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inputs.c"

#if defined(_WIN32) || defined(_WIN64)
    #define CLIPBOARD_CMD "clip"
#elif defined(__APPLE__) && defined(__MACH__)
    #define CLIPBOARD_CMD "pbcopy"
#elif defined(__linux__)
    #define CLIPBOARD_CMD "xclip -selection clipboard"
#else
    #error "Unsupported OS"
#endif

int get_height(FILE *file);
int get_width(FILE *file);
int chrcmp(char chr1, char chr2, int value1, int value2);
int str_sort(char *str1, char *str2);
int str_standard(char *str);
int get_words_num(char *_command);
char **read_file(FILE *file);
int write_file(FILE *file, char **text, int height);
char *get_plateform_name(char *str, char *separation_str);
char **sort(char **text, int height);
int exist(char **text, char *str, char *separation_str, int height);

int run_command(char *_command, char ***text, char *separation, int *height, int *width, int *running, int *rewritte);
int get_command(char *page, char **text, char *separation, int height);
int add_command(char *page, char *identifiant, char *password, char ***text, char *separation, int *height, int *width);
int remove_command(char *page, char ***text, char *separation, int *height, int *width);
int list_command(char **text, char *separation_str, int height);
int get_pass(char *name, char **text, char *separation_str, int height);
int add_pass(char *name, char *identifiant, char *password, char ***text, char *separation, int *height);
int remove_pass(char *name, char ***text, char *separation_str, int *height, int width);
int help(char *command);
int error_msg(char *message);

int main()
{
    char filename[] = "passwords.txt";
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        error_msg("Cannot open the file");
        return 1;
    }
    char **text = read_file(file);
    if (text == NULL)
    {
        error_msg("Cannot read the file");
        fclose(file);
        return 1;
    }
    
    char *separation = "     ", *command_line;
    int running = 1, rewritte = 0, width = get_width(file), height = get_height(file);
    fclose(file);
    text = sort(text, height);
    if (!width)
    {
        height = 0;
    }
    printf("\nTap help for more informations\n\n");
    while (running)
    {
        command_line = input("> ", 0);
        if (run_command(command_line, &text, separation, &height, &width, &running, &rewritte))
        {
            error_msg("Unknow command");
        }
        free(command_line);
    }
    if (rewritte)
    {    
        text = sort(text, height);
        FILE *end_file = fopen(filename, "w");
        if (end_file == NULL)
        {
            error_msg("Cannot open the file");
            return 1;
        }
        write_file(end_file, text, height);
        fclose(end_file);
        for (int i = 0; i < height; i++)
            free(text[i]);
    }
    free(text);
    return 0;
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

int chrcmp(char chr1, char chr2, int value1, int value2)
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
    int index = 0, indice = 0;
    while (str1[index] || str2[indice])
    {
        if (str1[index] == str2[indice])
        {
            if (str1[index]){index++;}
            if (str2[indice]){indice++;}
        }
        else
        {
            if ((str1[index] >= 65 && str1[index] <= 90) && (str2[index] >= 65 && str2[index] <= 90))
            {
                return chrcmp(str1[index], str2[index], 0, 0);
            }
            else if ((str1[index] >= 65 && str1[index] <= 90) && !(str2[index] >= 65 && str2[index] <= 90))
            {
                if (str1[index]+32 == str2[indice])
                {
                    return 0;
                }
                else
                {
                    return chrcmp(str1[index], str2[index], 32, 0);
                }
            }
            else if (!(str1[index] >= 65 && str1[index] <= 90) && (str2[index] >= 65 && str2[index] <= 90))
            {
                if (str1[index] == str2[indice]+32)
                {
                    return 1;
                }
                else
                {
                    return chrcmp(str1[index], str2[index], 0, 32);
                }
            }
            else
            {
                return chrcmp(str1[index], str2[index], 0, 0);
            }
        }
    }
    if (index < indice)
    {
        return 1;
    }
    else if (indice > index)
    {
        return 0;
    }
    return 0;
}

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

char *get_plateform_name(char *str, char *separation_str)
{
    int index = 0, separation_index, separation_length = strlen(separation_str);
    char *page = (char *)malloc(sizeof(char *) * strlen(str));
    if (page == NULL)
    {
        error_msg("Memory allocation error");
        return NULL;
    }
    separation_index = 0;
    while (separation_index < separation_length && str[index])
    {
        if (str[index] == separation_str[separation_index])
        {
            separation_index++;
        }
        else
        {
            separation_index = 0;
        }
        page[index] = str[index];
        index++;
    }
    page[index-separation_length] = '\0';
    return page;
}

char **sort(char **text, int height)
{
    if (!height || height == 1)
    {
        return text;
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height-1; j++)
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

int exist(char **text, char *name, char *separation_str, int height)
{
    for (int i = 0; i < height; i++)
    {
        char *plateform = get_plateform_name(text[i], separation_str);
        if (plateform == NULL)
        {
            exit(1);
        }
        if (!strcmp(plateform, name))
        {
            free(plateform);
            return 1;
        }
        free(plateform);
    }
    return 0;
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

int get_words_num(char *string)
{
    int words = 0, index = 0, is_word = 0;
    while (string[index])
    {
        if (string[index] >= 33 && string[index] <= 126)
        {
            is_word = 1;
        }
        else if (string[index] == ' ')
        {
            if (is_word)
            {
                words++;
                is_word = 0;
            }
        }
        if (string[index+1] == '\0')
        {
            if (is_word)
            {
                words++;
            }
        }
        index++;
    }
    return words;
}

int run_command(char *_command, char ***text, char *separation, int *height, int *width, int *running, int *rewritte)
{
    int length = get_words_num(_command);
    char args[length][strlen(_command)];
    int index = 0, indice = 0, _index = 0, is_word = 0;
    char word[strlen(_command)];
    while (_command[index])
    {
        if (_command[index] >= 33 && _command[index] <= 126)
        {
            word[_index] = _command[index];
            is_word = 1;
            _index++;
        }
        else if (_command[index] == ' ')
        {
            if (is_word)
            {
                word[_index] = '\0';
                strcpy(args[indice], word);
                indice++;
                is_word = 0;
                _index = 0;
            }
        }
        else
        {
            error_msg("Name standard isn't respected");
            return 0;
        }
        if (_command[index+1] == '\0')
        {
            if (is_word)
            {
                word[_index] = '\0';
                strcpy(args[indice], word);
            }
        }
        index++;
    }
    if (!strcmp(args[0], "list") || !strcmp(args[0], "ls"))
    {
        if (length > 1)
        {
            error_msg("Too much arguments");
        }
        else
        {
            list_command(*text, separation, *height);
        }
        return 0;
    }
    else if (!strcmp(args[0], "get"))
    {
        if (!(*height))
        {
            error_msg("There is no passwords you can get");
        }
        else if (length > 2)
        {
            error_msg("Too much arguments");
        }
        else if (length < 2)
        {
            error_msg("Not enough arguments");
        }
        else
        {
            get_command(args[1], *text, separation, *height);
        }
        return 0;
    }
    else if (!strcmp(args[0], "add"))
    {
        if (length > 4)
        {
            error_msg("Too much arguments");
        }
        else if (length < 4)
        {
            error_msg("Not enough arguments");
        }
        else
        {
            if (!add_command(args[1],args[2],args[3], text, separation, height, width))
            {
                *rewritte = 1;
            }
        }
        return 0;
    }
    else if (!strcmp(args[0], "remove") || !strcmp(args[0], "rm"))
    {
        if (!(*height))
        {
            error_msg("There is no passwords to remove");
        }
        else if (length > 2)
        {
            error_msg("Too much arguments");
        }
        else if (length < 2)
        {
            error_msg("Not enough arguments");
        }
        else
        {
            if (!remove_command(args[1], text, separation, height, width))
            {
                *rewritte = 1;
            }
        }
        return 0;
    }
    else if (!strcmp(args[0], "help") || !strcmp(args[0], "?"))
    {
        if (length > 2)
        {
            error_msg("Too much arguments");
        }
        else
        {
            if (length == 2)
            {
                help(args[1]);
            }
            else
            {
                help(NULL);
            }
        }
        return 0;
    }
    else if (!strcmp(args[0], "exit") || !strcmp(args[0], "quit"))
    {
        if (length > 1)
        {
            error_msg("Too much arguments");
        }
        else
        {
            *running = 0;
        }
        return 0;
    }
    return 1;
}

int get_command(char *page, char **text, char *separation, int height)
{
    if (get_pass(page, text, separation, height))
    {
        return 1;
    }
    return 0;
}

int add_command(char *page, char *identifiant, char *password, char ***text, char *separation, int *height, int *width)
{
    if (exist(*text, page, separation, *height))
    {
        error_msg("This plateform already exist");
        return 1;
    }
    int output = add_pass(page, identifiant, password, text, separation, height);
    if (output < 0)
    {
        error_msg("Cannot add the password");
        return 1;
    }
    else
    {
        *width = output;
    }
    (*text) = sort(*text, *height);
    return 0;
}

int remove_command(char *page, char ***text, char *separation, int *height, int *width)
{
    int output = remove_pass(page, text, separation, height, *width);
    if (output < 0)
    {
        return 1;
    }
    else
    {
        *width = output;
    }
    (*text) = sort(*text, *height);
    return 0;
}

int get_pass(char *name, char **text, char *separation_str, int height)
{
    int find = 0, index = 0, indice, separation_index, separation_length = strlen(separation_str);
    char *page, *identifiant, *password;
    for (int line = 0; line < height; line++)
    {
        page = get_plateform_name(text[line], separation_str);
        if (page == NULL)
        {
            error_msg("Cannot get the plateforme name");
            return 1;
        }
        //if the aksing plateform name and the one finded are the same, get the identifiant and password
        if (!strcmp(name, page))
        {
            index += strlen(page) + strlen(separation_str);
            find = 1;
            //get the identifiant
            identifiant = (char *)malloc(strlen(text[line]) * sizeof(char));
            if (identifiant == NULL)
            {
                free(page);
                error_msg("Memory allocation error");
                return 1;
            }
            indice = separation_index = 0;
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
                identifiant[indice] = text[line][index];
                index++;
                indice++;
            }
            identifiant[indice-separation_length] = '\0';
            //get the password
            password = (char *)malloc(strlen(text[line]) * sizeof(char));
            if (password == NULL)
            {
                free(page);
                free(identifiant);
                error_msg("Memory allocation error");
                return 1;
            }
            indice = 0;
            while (text[line][index] && text[line][index] != 10 && text[line][index] != 13)
            {
                password[indice] = text[line][index];
                indice++;
                index++;
            }
            password[indice] = '\0';
            break;
        }
        else
        {
            free(page);
        }
    }
    if (!find)
    {
        error_msg("The given name is inexisting or incorrect");
        return 1;
    }
    //display the informations
    printf("\n > Plateform : %s\n", page);
    printf(" > Identifiant : %s\n", identifiant);
    printf(" > Password : %s\n\n", password);

    FILE *clipboard = popen(CLIPBOARD_CMD, "w");
    if (clipboard == NULL)
    {
        free(page);
        free(identifiant);
        free(password);
        error_msg("Failed to open clipboard");
        return 1;
    }
    fprintf(clipboard, password);
    pclose(clipboard);

    printf("Password copied !\n\n");
    free(page);
    free(identifiant);
    free(password);
    return 0;
}

int add_pass(char *name, char *identifiant, char *password, char ***text, char *separation, int *height)
{
    int lenght = strlen(name)+strlen(identifiant)+strlen(password)+strlen(separation)*2+1;

    *text = (char **)realloc(*text, ((*height)+1) * sizeof(char *));
    if (*text == NULL)
    {
        printf("realloc ?\n");
        error_msg("Memory allocation error");
        return -1;
    }
    (*text)[*height] = (char *)malloc(lenght * sizeof(char));
    if ((*text)[*height] == NULL)
    {
        error_msg("Memory allocation error");
        return -1;
    }

    char line[lenght];
    line[0] = '\0';
    strcat(line, name);
    strcat(line, separation);
    strcat(line, identifiant);
    strcat(line, separation);
    strcat(line, password);

    (*text)[*height][0] = '\0';
    strcat((*text)[*height], line);
    (*height)++;
    return lenght-1;
}

int remove_pass(char *name, char ***text, char *separation_str, int *height, int width)
{
    int line_index, find = 0, separation_index, separation_length = strlen(separation_str);
    char *page;
    for (int line = 0; line < *height; line++)
    {
        int index = 0;
        separation_index = 0;
        page = get_plateform_name(((*text)[line]), separation_str);
        if (page == NULL)
        {
            exit(1);
        }
        if (!strcmp(name, page))
        {
            free(page);
            line_index = line;
            find = 1;
            break;
        }
        else
        {
            free(page);
        }
    }
    if (find)
    {
        if (*height == 1)
        {
            ***text = '\0';
            (*height)--;
            return 0;
        }
        if (line_index != (*height)-1)
            free(*((*text)+line_index));
            *((*text)+line_index) = *((*text)+(*height-1));
        (*height)--;
        *text = realloc(*text, (*height) * sizeof(char *));
        if (*text == NULL)
        {
            error_msg("Memory allocation error");
            return -1;
        }
    }
    else
    {
        error_msg("The given name is inexisting or incorrect");
        return -1;
    }
    return width;
}

int list_command(char **text, char *separation_str, int height)
{
    if (!height)
    {
        error_msg("There is no passwords to list");
        return 1;
    }
    char *page;
    printf("\n");
    for (int line = 0; line < height; line++)
    {
        page = get_plateform_name(text[line], separation_str);
        if (page == NULL)
        {
            exit(1);
        }
        printf(" > %s\n", page);
        free(page);
    }
    printf("\n");
    return 0;
}

int help(char *command)
{
    if (command == NULL)
    {
        printf("\n > add : ADD an identifiant and a password with a plateform name you can access with it\n");
        printf("\n > exit : EXIT the program\n");
        printf("\n > get : GET an identifiant and a password from a plateform name\n");
        printf("\n > help : DISPLAY the description of the commands and their function\n");
        printf("\n > list : DISPLAY all the plateform's names you can access\n");
        printf("\n > remove : REMOVE an identifiant and a password from a plateform name\n\n");
    }
    else
    {
        if (!strcmp(command, "list") || !strcmp(command, "ls"))
        {
            printf("\n > list [no args]\n");
            printf("\n  > DISPLAY all the plateform's names you can access\n\n");
        }
        else if (!strcmp(command, "get"))
        {
            printf("\n > get [name]\n");
            printf("\n  > GET an identifiant and a password from a plateform name\n\n");
        }
        else if (!strcmp(command, "add"))
        {
            printf("\n > add [name] [identifiant] [password]\n");
            printf("\n  > ADD an identifiant and a password with a plateform name you can access with it\n\n");
        }
        else if (!strcmp(command, "remove") || !strcmp(command, "rm"))
        {
            printf("\n > remove [name]\n");
            printf("\n  > REMOVE an identifiant and a password from a plateform name\n\n");
        }
        else if (!strcmp(command, "help") || !strcmp(command, "?"))
        {
            printf("\n > help [command]\n");
            printf("\n  > DISPLAY the description of the commands and their function\n\n");
        }
        else if (!strcmp(command, "exit") || !strcmp(command, "quit"))
        {
            printf("\n > exit [no args]\n");
            printf("\n  > EXIT the program\n\n");
        }
        else
        {
            error_msg("Unkown command");
        }
    }
    return 0;
}

int error_msg(char *message)
{
    fprintf(stderr, "\n    Error : %s\n\n", message);
    return 0;
}
