#include "../manager.h"

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
