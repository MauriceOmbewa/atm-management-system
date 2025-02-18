#include <termios.h>
#include "header.h"

char *USERS = "./data/users.txt";



const char *getPassword(struct User u)
{
    FILE *fp;
    struct User userChecker;
    static char passwordBuffer[50];

    if ((fp = fopen("./data/users.txt", "r")) == NULL)
    {
        printf("Error! opening file\n");
        exit(1);
    }

    while (fscanf(fp, "%d %s %s", &userChecker.id, userChecker.name, userChecker.password) == 3)
    {
        if (strcmp(userChecker.name, u.name) == 0)
        {
            fclose(fp);
            strcpy(passwordBuffer, userChecker.password);
            // char *buff = userChecker.password;
            return passwordBuffer;
        }
    }

    fclose(fp);
    return "no user found";
}