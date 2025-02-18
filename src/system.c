#include "header.h"

const char *RECORDS = "./data/records.txt";

int getAccountFromFile(FILE *ptr, char name[50], struct Record *r)
{
    return fscanf(ptr, "%d %d %s %d %d/%d/%d %s %d %lf %s",
                &r->id,
		        &r->userId,
		        name,
                &r->accountNbr,
                &r->deposit.month,
                &r->deposit.day,
                &r->deposit.year,
                r->country,
                &r->phone,
                &r->amount,
                r->accountType) != EOF;
}

void saveAccountToFile(FILE *ptr, struct User u, struct Record r)
{
    char line[256]; 
    int len = 0;

    rewind(ptr);

    while (fgets(line, sizeof(line), ptr)) {
        if (line[strlen(line) - 1] == '\n') { 
            len++; 
        }
    }
    r.id = (len / 2); 

    fseek(ptr, 0, SEEK_END);

    fprintf(ptr, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
            r.id,
            u.id,
            u.name,
            r.accountNbr,
            r.deposit.month,
            r.deposit.day,
            r.deposit.year,
            r.country,
            r.phone,
            r.amount,
            r.accountType);
}

void stayOrReturn(int notGood, void f(struct User u), struct User u)
{
    int option;
    if (notGood == 0)
    {
        system("clear");
        printf("\n✖ Record not found!!\n");
    invalid:
        printf("\nEnter 0 to try again, 1 to return to main menu and 2 to exit:");
        scanf("%d", &option);
        if (option == 0)
            f(u);
        else if (option == 1)
            mainMenu(u);
        else if (option == 2)
            exit(0);
        else
        {
            printf("Insert a valid operation!\n");
            goto invalid;
        }
    }
    else
    {
        printf("\nEnter 1 to go to the main menu and 0 to exit:");
        scanf("%d", &option);
    }
    if (option == 1)
    {
        system("clear");
        mainMenu(u);
    }
    else
    {
        system("clear");
        exit(1);
    }
}

void success(struct User u)
{
    int option;
    printf("\n✔ Success!\n\n");
invalid:
    printf("Enter 1 to go to the main menu and 0 to exit!\n");
    scanf("%d", &option);
    system("clear");
    if (option == 1)
    {
        mainMenu(u);
    }
    else if (option == 0)
    {
        exit(1);
    }
    else
    {
        printf("Insert a valid operation!\n");
        goto invalid;
    }
}

void createNewAcc(struct User u)
{
    struct Record r;
    struct Record cr;
    char userName[50];
    FILE *pf = fopen(RECORDS, "a+");
    FILE *uf = fopen("./data/users.txt", "r");
    char line[100];
    char fileUserName[50];
    char password[50];
    int fileUserId;

    noAccount:
    system("clear");
    printf("\t\t\t===== New record =====\n");

    // Find the user ID from users.txt
    while (fgets(line, sizeof(line), uf))
    {
        sscanf(line, "%d %s %s", &fileUserId, fileUserName, password);
        if (strcmp(fileUserName, u.name) == 0)
        {
            u.id = fileUserId;
            break;
        }
    }
    rewind(uf);

    printf("\nEnter today's date(mm/dd/yyyy):");
    scanf("%d/%d/%d", &r.deposit.month, &r.deposit.day, &r.deposit.year);
    printf("\nEnter the account number:");
    scanf("%d", &r.accountNbr);

    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == r.accountNbr)
        {
            printf("✖ This Account already exists for this user\n\n");
            goto noAccount;
        }
    }
    printf("\nEnter the country:");
    scanf("%s", r.country);
    printf("\nEnter the phone number:");
    scanf("%d", &r.phone);
    printf("\nEnter amount to deposit: $");
    scanf("%lf", &r.amount);
    printf("\nChoose the type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\n\n\tEnter your choice:");
    scanf("%s", r.accountType);

    saveAccountToFile(pf, u, r);

    fclose(pf);
    fclose(uf);
    success(u);
}

void updateAccount(struct User u)
{
    struct Record r, cr;
    char userName[50];
    int accountNumber, found = 0;

    FILE *pf = fopen(RECORDS, "r");  // Open existing file for reading
    FILE *temp = fopen("temp.txt", "w"); // Temporary file for writing

    if (pf == NULL || temp == NULL)
    {
        perror("Error opening file");
        return;
    }

    system("clear");
    printf("\t\t===== Update Account Details =====\n");
    printf("\nEnter the account number to update: ");
    scanf("%d", &accountNumber);

    while (getAccountFromFile(pf, userName, &cr))
    {
        if (strcmp(userName, u.name) == 0 && cr.accountNbr == accountNumber)
        {
            found = 1;

            printf("\nEnter updated country: ");
            scanf("%s", r.country);
            printf("\nEnter updated phone number: ");
            scanf("%d", &r.phone);
            printf("\nEnter new amount to deposit: $");
            scanf("%lf", &r.amount);
            printf("\nChoose new type of account:\n\t-> saving\n\t-> current\n\t-> fixed01(for 1 year)\n\t-> fixed02(for 2 years)\n\t-> fixed03(for 3 years)\nEnter your choice: ");
            scanf("%s", r.accountType);

            // Preserve other details while updating user inputs
            r.id = cr.id;
            r.accountNbr = cr.accountNbr;
            r.deposit = cr.deposit;

            // Write updated details
            fprintf(temp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                    r.id, u.id, u.name, r.accountNbr,
                    r.deposit.month, r.deposit.day, r.deposit.year,
                    r.country, r.phone, r.amount, r.accountType);
        }
        else
        {
            // Keep existing records unchanged
            fprintf(temp, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                    cr.id, cr.userId, userName, cr.accountNbr,
                    cr.deposit.month, cr.deposit.day, cr.deposit.year,
                    cr.country, cr.phone, cr.amount, cr.accountType);
        }
    }

    fclose(pf);
    fclose(temp);

    if (!found)
    {
        printf("\n✖ Account not found!\n");
        remove("temp.txt");
    }
    else
    {
        remove(RECORDS);
        rename("temp.txt", RECORDS);
        printf("\n✔ Account updated successfully!\n");
    }

    success(u);
}

void checkSpecificAccount(struct User u)
{
    struct Record r;
    char userName[50];
    int accountNumber, found = 0;

    FILE *pf = fopen(RECORDS, "r"); // Open file for reading
    if (pf == NULL)
    {
        perror("Error opening file");
        return;
    }

    system("clear");
    printf("\t\t===== Check Specific Account =====\n\n");

    // Ask for the account number
    printf("Enter the account number you want to check: ");
    scanf("%d", &accountNumber);

    // Search for the account in the file
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && r.accountNbr == accountNumber)
        {
            // Print the account details
            printf("\n✔ Account Found!\n");
            printf("_____________________\n");
            printf("Account number: %d\n", r.accountNbr);
            printf("Deposit Date: %d/%d/%d\n", r.deposit.month, r.deposit.day, r.deposit.year);
            printf("Country: %s\n", r.country);
            printf("Phone number: %d\n", r.phone);
            printf("Amount deposited: $%.2f\n", r.amount);
            printf("Account Type: %s\n", r.accountType);
            found = 1;
            break; // Exit loop since we found the account
        }
    }

    fclose(pf); // Close file

    // If no account was found, inform the user
    if (!found)
    {
        printf("\n✖ No account found with number %d for user %s.\n", accountNumber, u.name);
    }

    success(u); // Optionally call success after the process
}


void checkAllAccounts(struct User u)
{
    char userName[100];
    struct Record r;

    FILE *pf = fopen(RECORDS, "r");

    system("clear");
    printf("\t\t====== All accounts from user, %s =====\n\n", u.name);
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0)
        {
            printf("_____________________\n");
            printf("\nAccount number:%d\nDeposit Date:%d/%d/%d \ncountry:%s \nPhone number:%d \nAmount deposited: $%.2f \nType Of Account:%s\n",
                   r.accountNbr,
                   r.deposit.day,
                   r.deposit.month,
                   r.deposit.year,
                   r.country,
                   r.phone,
                   r.amount,
                   r.accountType);
        }
    }
    fclose(pf);
    success(u);
}

void removeAccount(struct User u)
{
    struct Record r;
    char userName[50];
    int accountNumber, found = 0;

    FILE *pf = fopen(RECORDS, "r");  // Open records file for reading
    FILE *tempFile = fopen("temp.txt", "w");  // Temporary file to store updated data

    if (pf == NULL || tempFile == NULL)
    {
        perror("Error opening file");
        return;
    }

    system("clear");
    printf("\t\t===== Remove Account =====\n\n");

    // Ask user for the account number
    printf("Enter the account number to remove: ");
    scanf("%d", &accountNumber);

    // Read each account and copy to temp file, excluding the one being deleted
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && r.accountNbr == accountNumber)
        {
            printf("\n✔ Account %d has been removed successfully!\n", accountNumber);
            found = 1; // Account found
            continue;  // Skip writing this account to the temp file (delete it)
        }
        // Write remaining accounts to temp file
        fprintf(tempFile, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                r.id,
                u.id,
                userName,
                r.accountNbr,
                r.deposit.month,
                r.deposit.day,
                r.deposit.year,
                r.country,
                r.phone,
                r.amount,
                r.accountType);
    }

    fclose(pf);
    fclose(tempFile);

    // If no account was found, notify the user and delete temp file
    if (!found)
    {
        printf("\n✖ No account found with number %d for user %s.\n", accountNumber, u.name);
        remove("temp.txt"); // Remove temp file as it's not needed
    }
    else
    {
        remove(RECORDS);          // Delete old records file
        rename("temp.txt", RECORDS); // Rename temp file to records file
    }

    success(u); // Call success function to return to menu or exit
}

void transferAccountOwnership(struct User u)
{
    struct Record r;
    char userName[50], newOwner[50];
    int accountNumber, found = 0;

    FILE *pf = fopen(RECORDS, "r"); 
    FILE *tempFile = fopen("temp.txt", "w");  

    if (pf == NULL || tempFile == NULL)
    {
        perror("Error opening file");
        return;
    }

    system("clear");
    printf("\t\t===== Transfer Account Ownership =====\n\n");

    printf("Enter the account number to transfer: ");
    scanf("%d", &accountNumber);

    // Check if the account exists and belongs to the current user
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && r.accountNbr == accountNumber)
        {
            found = 1;
            printf("\n✔ Account %d found! Enter the new owner's username: ", accountNumber);
            scanf("%s", newOwner); 
            
            // Update the owner of the account
            strcpy(userName, newOwner);
        }
        fprintf(tempFile, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                r.id,
                u.id,
                userName,
                r.accountNbr,
                r.deposit.month,
                r.deposit.day,
                r.deposit.year,
                r.country,
                r.phone,
                r.amount,
                r.accountType);
    }

    fclose(pf);
    fclose(tempFile);

    if (found)
    {
        remove(RECORDS);
        rename("temp.txt", RECORDS);
        printf("\n✔ Account %d has been successfully transferred to %s!\n", accountNumber, newOwner);
    }
    else
    {
        printf("\n✖ No account found with number %d for user %s.\n", accountNumber, u.name);
        remove("temp.txt"); 
    }

    success(u); 
}

void makeTransaction(struct User u)
{
    struct Record r;
    char userName[50];
    int accountNumber, found = 0, transactionType;
    double amount;

    FILE *pf = fopen(RECORDS, "r");  // Open the file for reading
    FILE *tempFile = fopen("temp.txt", "w");  // Temporary file for updates

    if (pf == NULL || tempFile == NULL)
    {
        perror("Error opening file");
        return;
    }

    system("clear");
    printf("\t\t===== Make a Transaction =====\n\n");

    // Ask the user for the account number
    printf("Enter your account number: ");
    scanf("%d", &accountNumber);

    // Look for the account in the file
    while (getAccountFromFile(pf, userName, &r))
    {
        if (strcmp(userName, u.name) == 0 && r.accountNbr == accountNumber)
        {
            found = 1;
            printf("\n✔ Account %d found! Current balance: $%.2lf\n", r.accountNbr, r.amount);
            
            // Ask user for the transaction type
            printf("\nSelect transaction type:\n1 - Deposit\n2 - Withdraw\nEnter choice: ");
            scanf("%d", &transactionType);

            // Handle deposit
            if (transactionType == 1)
            {
                printf("\nEnter deposit amount: $");
                scanf("%lf", &amount);
                r.amount += amount;
                printf("\n✔ Successfully deposited $%.2lf. New balance: $%.2lf\n", amount, r.amount);
            }
            // Handle withdrawal
            else if (transactionType == 2)
            {
                printf("\nEnter withdrawal amount: $");
                scanf("%lf", &amount);
                if (amount > r.amount)
                {
                    printf("\n✖ Insufficient funds! Transaction canceled.\n");
                }
                else
                {
                    r.amount -= amount;
                    printf("\n✔ Successfully withdrew $%.2lf. New balance: $%.2lf\n", amount, r.amount);
                }
            }
            else
            {
                printf("\n✖ Invalid transaction type! No changes made.\n");
            }
        }

        // Write updated or original data to temp file
        fprintf(tempFile, "%d %d %s %d %d/%d/%d %s %d %.2lf %s\n\n",
                r.id,
                u.id,
                userName,
                r.accountNbr,
                r.deposit.month,
                r.deposit.day,
                r.deposit.year,
                r.country,
                r.phone,
                r.amount,
                r.accountType);
    }

    fclose(pf);
    fclose(tempFile);

    // If account was found, update the main file
    if (found)
    {
        remove(RECORDS);
        rename("temp.txt", RECORDS);
        printf("\n✔ Transaction completed successfully!\n");
    }
    else
    {
        printf("\n✖ No account found with number %d for user %s.\n", accountNumber, u.name);
        remove("temp.txt"); // Remove temp file since no updates were made
    }

    success(u); // Allow the user to return to the menu or exit
}