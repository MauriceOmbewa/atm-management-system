#include <termios.h>
#include "header.h"

char *USERS = "./data/users.txt";

void loginMenu(char username[50], char pass[50])
{
    struct termios oflags, nflags;

    system("clear");
    printf("\n\n\n\t\t\t\t   Bank Management System\n\t\t\t\t\t User Login: ");
    scanf("%49s", username); // Prevent buffer overflow

    // Disable password echo
    if (tcgetattr(fileno(stdin), &oflags) != 0)
    {
        perror("tcgetattr");
        return;
    }
    nflags = oflags;
    nflags.c_lflag &= ~ECHO;
    nflags.c_lflag |= ECHONL;

    if (tcsetattr(fileno(stdin), TCSANOW, &nflags) != 0)
    {
        perror("tcsetattr");
        return;
    }

    printf("\n\n\n\n\n\t\t\t\tEnter the password to login: ");
    scanf("%49s", pass); // Prevent buffer overflow

    // Restore terminal settings
    if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
    {
        perror("tcsetattr");
        return;
    }
}

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