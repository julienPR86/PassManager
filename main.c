#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256

int exist(char *name);
int get_words_num(char *string);
char *get_plateform_name(char *str);
int error_msg(char *message);
int charcmp(char chr1, char chr2, int value1, int value2);
int str_sort(char *str1, char *str2);
char **sort(char **text);
int remove_command(char *page);
int remove_pass(char *name);
int run_command(char *_command, int *rewrite);
int list_command();
char *input(char *str, int returns);
int help(char *command);
int get_command(char *page);
int get_pass(char *name);
char **read_file(FILE *file);
int get_height(FILE *file);
int get_width(FILE *file);
int write_file(FILE *file);
int add_command(char *page, char *identifier, char *password, int overwrite);
int add_pass(char *name, char *identifier, char *password);
int overwrite_pass(char *name, char *identifier, char *password, int line_num);

const char *separation = "     ";
const char *filename = "passwords.txt";
int running = 1;
int text_height = 0;
int text_width = 0;
char **text = NULL;

int main(void)
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        error_msg("Cannot open the file");
        return 1;
    }
    text = read_file(file);
    text_height = get_height(file);
    text_width = get_width(file);
    if (text == NULL)
    {
        error_msg("Cannot read the file");
        fclose(file);
        return 1;
    }
    fclose(file);
    text = sort(text);
    if (!text_width)
    {
        text_height = 0;
    }
    char *command_line;
    int rewrite = 0;
    printf("\nTap help for more informations\n\n");
    while (running)
    {
        command_line = input("> ", 0);
        if (run_command(command_line, &rewrite))
        {
            error_msg("Unknow command");
        }
        free(command_line);
    }
    if (rewrite)
    {    
        text = sort(text);
        FILE *end_file = fopen(filename, "w");
        if (end_file == NULL)
        {
            error_msg("Cannot open the file");
            return 1;
        }
        write_file(end_file);
        fclose(end_file);
        for (int i = 0; i < text_height; i++)
            free(text[i]);
    }
    free(text);
    return 0;
}

int exist(char *name)
{
    for (int i = 0; i < text_height; i++)
    {
        char *plateform = get_plateform_name(text[i]);
        if (plateform == NULL)
        {
            exit(1);
        }
        if (!strcmp(plateform, name))
        {
            free(plateform);
            return i+1;
        }
        free(plateform);
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

char *get_plateform_name(char *str)
{
    int index = 0, separation_index, separation_length = strlen(separation);
    char *page = (char *)malloc(sizeof(char *) * strlen(str));
    if (page == NULL)
    {
        error_msg("Memory allocation error");
        return NULL;
    }
    separation_index = 0;
    while (separation_index < separation_length && str[index])
    {
        if (str[index] == separation[separation_index])
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

int error_msg(char *message)
{
    fprintf(stderr, "\n    Error : %s\n\n", message);
    return 0;
}

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

int remove_command(char *page)
{
    int new_width = remove_pass(page);
    if (new_width < 0)
    {
        return 1;
    }
    else
    {
        if (!new_width)
        {
            text_width = new_width;
        }
    }
    text = sort(text);
    return 0;
}

int remove_pass(char *name)
{
    int lineword_index, find = 0;
    char *page;
    for (int line = 0; line < text_height; line++)
    {
        page = get_plateform_name(text[line]);
        if (page == NULL)
        {
            exit(1);
        }
        if (!strcmp(name, page))
        {
            free(page);
            lineword_index = line;
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
        if (text_height == 1)
        {
            **text = '\0';
            text_height--;
            return 0;
        }
        if (lineword_index != text_height-1)
        {
            free((*text)+lineword_index);
            *((*text)+lineword_index) = *((*text)+text_height-1);
        }
        text_height--;
        text = realloc(text, text_height * sizeof(char *));
        if (text == NULL)
        {
            error_msg("Memory allocation error");
            return -1;
        }
    }
    else
    {
        error_msg("The given name is non-exitent or incorrect");
        return -1;
    }
    return text_width;
}

int run_command(char *_command, int *rewrite)
{
    int length = get_words_num(_command);
    char args[length][strlen(_command)];
    int index = 0, _index = 0, word_index = 0, is_word = 0;
    char word[strlen(_command)];
    while (_command[index])
    {
        if (_command[index] >= 33 && _command[index] <= 126)
        {
            word[word_index] = _command[index];
            is_word = 1;
            word_index++;
        }
        else if (_command[index] == ' ')
        {
            if (is_word)
            {
                word[word_index] = '\0';
                strcpy(args[_index], word);
                _index++;
                is_word = 0;
                word_index = 0;
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
                word[word_index] = '\0';
                strcpy(args[_index], word);
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
            list_command();
        }
        return 0;
    }
    else if (!strcmp(args[0], "get"))
    {
        if (!text_height)
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
            get_command(args[1]);
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
            if (!add_command(args[1],args[2],args[3], 0))
            {
                *rewrite = 1;
            }
        }
        return 0;
    }
    else if (!strcmp(args[0], "add!"))
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
            if (!add_command(args[1],args[2],args[3], 1))
            {
                *rewrite = 1;
            }
        }
        return 0;
    }
    else if (!strcmp(args[0], "remove") || !strcmp(args[0], "rm"))
    {
        if (!text_height)
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
            if (!remove_command(args[1]))
            {
                *rewrite = 1;
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
            running = 0;
        }
        return 0;
    }
    return 1;
}

int list_command()
{
    if (!text_height)
    {
        error_msg("There is no passwords to list");
        return 1;
    }
    char *page;
    printf("\n");
    for (int line = 0; line < text_height; line++)
    {
        page = get_plateform_name(text[line]);
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

int help(char *command)
{
    if (command == NULL)
    {
        printf("\n > add : ADD an identifier and a password with a plateform name you can access with it\n");
        printf("\n > exit : EXIT the program\n");
        printf("\n > get : GET an identifier and a password from a plateform name\n");
        printf("\n > help : DISPLAY the description of the commands and their function\n");
        printf("\n > list : DISPLAY all the plateform's names you can access\n");
        printf("\n > remove : REMOVE an identifier and a password from a plateform name\n\n");
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
            printf("\n  > GET an identifier and a password from a plateform name\n\n");
        }
        else if (!strcmp(command, "add"))
        {
            printf("\n > add [name] [identifier] [password]\n");
            printf("\n  > ADD an identifier and a password with a plateform name you can access with it\n\n");
        }
        else if (!strcmp(command, "remove") || !strcmp(command, "rm"))
        {
            printf("\n > remove [name]\n");
            printf("\n  > REMOVE an identifier and a password from a plateform name\n\n");
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

int get_command(char *page)
{
    if (get_pass(page))
    {
        return 1;
    }
    return 0;
}

int get_pass(char *name)
{
    int find = 0, index = 0, _index, separation_index, separation_length = strlen(separation);
    char *page, *identifier, *password;
    for (int line = 0; line < text_height; line++)
    {
        page = get_plateform_name(text[line]);
        if (page == NULL)
        {
            error_msg("Cannot get the plateform name");
            return 1;
        }
        //if the asking plateform name and the one found are the same, get the identifier and password
        if (!strcmp(name, page))
        {
            index += strlen(page) + strlen(separation);
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
                if (text[line][index] == separation[separation_index])
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

    /*FILE *clipboard = popen(CLIPBOARD_CMD, "w");
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

    printf("Password copied !\n");*/
    free(page);
    free(identifier);
    free(password);
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

int write_file(FILE *file)
{
    for (int i = 0; i < text_height; i++)
    {
        if (i != text_height-1)
            fprintf(file, "%s\n", text[i]);
        else
            fprintf(file, "%s", text[i]);
    }
    return 0;
}

int add_command(char *page, char *identifier, char *password, int overwrite)
{
    if (exist(page) && !overwrite)
    {
        error_msg("This plateform already exist");
        printf("Tap add! to overwrite\n");
        return 1;
    }
    int new_width;
    if (!overwrite)
    {
        new_width = add_pass(page, identifier, password);
    }
    else
    {
        int line = exist(page);
        if (line)
        {
            new_width = overwrite_pass(page, identifier, password, line);
        }
        else
        {
            new_width = add_pass(page, identifier, password);
        }
    }
    if (new_width < 0)
    {
        error_msg("Cannot add the password");
        return 1;
    }
    else
    {
        if (new_width > text_width)
        {
            text_width = new_width;
        }
    }
    text = sort(text);
    return 0;
}

int add_pass(char *name, char *identifier, char *password)
{
    int length = strlen(name)+strlen(identifier)+strlen(password)+strlen(separation)*2+1;

    text = (char **)realloc(text, (text_height+1) * sizeof(char *));
    if (text == NULL)
    {
        printf("realloc ?\n");
        error_msg("Memory allocation error");
        return -1;
    }
    text[text_height] = (char *)malloc(length * sizeof(char));
    if (text[text_height] == NULL)
    {
        error_msg("Memory allocation error");
        return -1;
    }

    char line[length];
    line[0] = '\0';
    strcat(line, name);
    strcat(line, separation);
    strcat(line, identifier);
    strcat(line, separation);
    strcat(line, password);

    text[text_height][0] = '\0';
    strcat(text[text_height], line);
    text_height++;
    return length-1;
}

int overwrite_pass(char *name, char *identifier, char *password, int line_num)
{
    int length = strlen(name)+strlen(identifier)+strlen(password)+strlen(separation)*2+1;

    char line[length];
    line[0] = '\0';
    strcat(line, name);
    strcat(line, separation);
    strcat(line, identifier);
    strcat(line, separation);
    strcat(line, password);

    strcpy(text[line_num-1], line);
    return length-1;
}
