#include "../manager.h"

int help(char *command)
{
    if (command == NULL)
    {
        if (is_modifiable)
        {
            printf("\n > add : ADD an identifier and a password with a plateform name you can access with it\n");
            printf("\n > data : DISPLAY or CHANGE the actual data path\n");
            printf("\n > exit : EXIT the program\n");
            printf("\n > get : GET an identifier and a password from a plateform name\n");
            printf("\n > help : DISPLAY the description of the commands and their function\n");
            printf("\n > list : DISPLAY all the plateform's names you can access\n");
            printf("\n > remove : REMOVE an identifier and a password from a plateform name\n\n");
        }
        else
        {
            printf("\n > data : DISPLAY or CHANGE the actual data path\n");
            printf("\n > exit : EXIT the program\n");
            printf("\n > help : DISPLAY the description of the commands and their function\n\n");
        }
    }
    else
    {
        if (!strcmp(command, "list") || !strcmp(command, "ls"))
        {
            printf("\n > list []\n");
            printf("\n  > DISPLAY all the plateform's names you can access\n\n");
        }
        else if (!strcmp(command, "data"))
        {
            printf("\n > data path []\n");
            printf("\n  > DISPLAY the actual data path\n");
            printf("\n > data change [path]\n");
            printf("\n  > Change the data path to [path]\n\n");
        }
        else if (!strcmp(command, "get"))
        {
            printf("\n > get [name]\n");
            printf("\n  > GET an identifier and a password from a plateform name\n\n");
        }
        else if (!strcmp(command, "add"))
        {
            printf("\n > add [name] [identifier] [password]\n");
            printf("\n  > ADD an identifier and a password with a plateform name you can access with it\n");
            printf("\n   > Write <rand> for a random passwords in password argument\n\n");
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
            printf("\n > exit []\n");
            printf("\n  > EXIT the program\n\n");
        }
        else
        {
            error_msg("Unkown command");
        }
    }
    return 0;
}
