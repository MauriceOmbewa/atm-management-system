#include <termios.h>
#include "header.h"

char *USERS = "./data/users.txt";

void loginMenu(char username[50], char pass[50])
{
    
    system("clear");
    printf("\n\n\n\t\t\t\t Bank Management System");
    struct termios oflags, nflags;
    char buffer[100]; // Buffer for fgets
    space:
    printf("\n\t\t\t\t\t User Login: ");
    
    // Clear input buffer first
    int c;
    if (stdin->_IO_read_ptr != stdin->_IO_read_end) {
        while ((c = getchar()) != '\n' && c != EOF) {} // Clear pending input
    }
    
    // Get username
    fgets(username, 50, stdin);
    if (strchr(username, ' ') != NULL)
    {
        printf("\n✖ Username cannot contain spaces.\n");
        exit(1);
    }
    username[strcspn(username, "\n")] = 0; // Remove trailing newline
    
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
    fgets(pass, 50, stdin);
    if (strchr(pass, ' ') != NULL){
        printf("\n✖ Password cannot contain spaces.\n");
            // Restore terminal settings
        if (tcsetattr(fileno(stdin), TCSANOW, &oflags) != 0)
        {
            perror("tcsetattr");
        }
        exit(1);
    }
    pass[strcspn(pass, "\n")] = 0; // Remove trailing newline
    
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