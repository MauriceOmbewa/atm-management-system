#include "header.h"

#define USERS_FILE "./data/users.txt"

void mainMenu(struct User u)
{
    int option;
    system("clear");
    printf("\n\n\t\t======= ATM =======\n\n");
    printf("\n\t\t-->> Feel free to choose one of the options below <<--\n");
    printf("\n\t\t[1]- Create a new account\n");
    printf("\n\t\t[2]- Update account information\n");
    printf("\n\t\t[3]- Check accounts\n");
    printf("\n\t\t[4]- Check list of owned account\n");
    printf("\n\t\t[5]- Make Transaction\n");
    printf("\n\t\t[6]- Remove existing account\n");
    printf("\n\t\t[7]- Transfer ownership\n");
    printf("\n\t\t[8]- Exit\n");
    scanf("%d", &option);

    switch (option)
    {
    case 1:
        createNewAcc(u);
        break;
    case 2:
        updateAccount(u);
        break;
    case 3:
    checkSpecificAccount(u);
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        makeTransaction(u);
        break;
    case 6:
        removeAccount(u);
        break;
    case 7:
        transferAccountOwnership(u);
        break;
    case 8:
        exit(1);
        break;
    default:
        printf("Invalid operation!\n");
    }
};

void registerUser(struct User *u)
{
    username_exists:
    FILE *file = fopen(USERS_FILE, "r");
    if (file == NULL)
    {
        // If file doesn't exist, assume no users are registered yet
        file = fopen(USERS_FILE, "a+");
        if (file == NULL)
        {
            perror("Error opening file");
            return;
        }
    }

    int validUsername;
    do {
        validUsername = 1;
        printf("\nEnter username: ");
        scanf("%s", u->name);

        // Check if username is strictly made of alphabets and has at least 2 alphabets
        if (strlen(u->name) < 2)
        {
            printf("\n✖ Username must have at least 2 alphabets. Try again.\n");
            validUsername = 0;
            continue;
        }

        for (int i = 0; i < strlen(u->name); i++)
        {
            if (!isalpha(u->name[i]))
            {
                printf("\n✖ Username must be strictly made of alphabets. Try again.\n");
                validUsername = 0;
                break;
            }
        }
    } while (!validUsername);

    printf("\nEnter password: ");
    scanf("%s", u->password);

    struct User tempUser;
    int lastId = -1;
    int usernameExists = 0;

    while (fscanf(file, "%d %s %s\n", &tempUser.id, tempUser.name, tempUser.password) == 3)
    {
        if (strcmp(tempUser.name, u->name) == 0) // Compare scanned username with existing usernames
        {
            printf("\n✖ Username '%s' already exists. Try another.\n", u->name);
            goto username_exists;
        }
        lastId = tempUser.id; // Keep track of last user ID
    }
    fclose(file);

    // Assign new user ID
    u->id = lastId + 1;

    file = fopen(USERS_FILE, "a");
    if (file == NULL)
    {
        perror("Error opening file for writing");
        return;
    }

    fprintf(file, "%d %s %s\n", u->id, u->name, u->password);
    printf("\n✔ User '%s' registered successfully with ID %d!\n", u->name, u->id);

    fclose(file);
    return;
}

void initMenu(struct User *u)
{
    char option[10];
    system("clear");
    printf("\n\n\t\t======= ATM =======\n");
    printf("\n\t\t-->> Feel free to login / register :\n");
    printf("\n\t\t[1]- login\n");
    printf("\n\t\t[2]- register\n");
    printf("\n\t\t[3]- exit\n");

    while (1)
    {
        printf("Enter your option: ");
        scanf("%s", option);

        if (strlen(option) != 1 || option[0] < '1' || option[0] > '3')
        {
            printf("Invalid input! Please enter a single digit number (1, 2, or 3).\n");
            continue;
        }

        break;
    }

    switch (option[0])
    {
    case '1':
        loginMenu(u->name, u->password);
        const char *savedPassword = getPassword(*u);
        if (savedPassword == NULL)
        {
            printf("\nWrong password!! or User Name\n");
            exit(1);
        }

        if (strcmp(u->password, savedPassword) == 0)
        {
            printf("\n\n✔ Password Match! Login successful!\n");
        }
        else
        {
            printf("\nWrong password!! or User Name\n");
            exit(1);
        }
        return;

    case '2':
        registerUser(u);
        return;

    case '3':
        exit(0);

    default:
        printf("Insert a valid operation!\n");
    }
}

int main()
{
    struct User u;
    
    initMenu(&u);
    mainMenu(u);
    return 0;
}
