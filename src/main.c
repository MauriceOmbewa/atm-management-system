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
        // student TODO : add your **Update account information** function
        // here
        break;
    case 3:
    checkSpecificAccount(u);
        // student TODO : add your **Check the details of existing accounts** function
        // here
        break;
    case 4:
        checkAllAccounts(u);
        break;
    case 5:
        // student TODO : add your **Make transaction** function
        // here
        break;
    case 6:
        removeAccount(u);
        // student TODO : add your **Remove existing account** function
        // here
        break;
    case 7:
        // student TODO : add your **Transfer owner** function
        // here
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
    FILE *file = fopen(USERS_FILE, "r"); // Open the file in read mode to check for existing usernames
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

    // Get new user details first
    printf("\nEnter username: ");
    scanf("%s", u->name);
    printf("\nEnter password: ");
    scanf("%s", u->password);

    struct User tempUser;
    int lastId = -1; // Start with -1 so first user gets ID 0
    int usernameExists = 0;

    // Read existing users and check if the username already exists
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
    int r = 0;
    int option;
    system("clear");
    printf("\n\n\t\t======= ATM =======\n");
    printf("\n\t\t-->> Feel free to login / register :\n");
    printf("\n\t\t[1]- login\n");
    printf("\n\t\t[2]- register\n");
    printf("\n\t\t[3]- exit\n");
    while (!r)
    {
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            loginMenu(u->name, u->password);
            if (strcmp(u->password, getPassword(*u)) == 0)
            {
                printf("\n\nPassword Match!");
            }
            else
            {
                printf("\nWrong password!! or User Name\n");
                exit(1);
            }
            r = 1;
            break;
        case 2:
            // student TODO : add your **Registration** function
            // here
            registerUser(u);
            r = 1;
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("Insert a valid operation!\n");
        }
    }
};

int main()
{
    struct User u;
    
    initMenu(&u);
    mainMenu(u);
    return 0;
}
