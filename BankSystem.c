#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define DATA_FILE "bank_data.txt"

typedef struct {
    int accountNumber;
    char name[MAX_NAME_LENGTH];
    double balance;
} Account;

// Function prototypes
void createAccount();
void viewAccounts();
void depositMoney();
void withdrawMoney();
void checkBalance();
void saveAccount(Account account);
void menu();

int main() {
    menu();
    return 0;
}

// Menu function
void menu() {
    int choice;
    do {
        printf("\n--- Bank System Simulator ---\n");
        printf("1. Create Account\n");
        printf("2. View All Accounts\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Check Balance\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: createAccount(); break;
            case 2: viewAccounts(); break;
            case 3: depositMoney(); break;
            case 4: withdrawMoney(); break;
            case 5: checkBalance(); break;
            case 6: printf("Exiting... Thank you!\n"); exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);
}

// Function to create a new account
void createAccount() {
    Account newAccount;
    FILE *file = fopen(DATA_FILE, "a");

    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &newAccount.accountNumber);
    printf("Enter account holder name: ");
    scanf(" %[^\n]", newAccount.name);
    newAccount.balance = 0;

    fwrite(&newAccount, sizeof(Account), 1, file);
    fclose(file);

    printf("Account created successfully!\n");
}

// Function to view all accounts
void viewAccounts() {
    FILE *file = fopen(DATA_FILE, "r");
    Account account;

    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n--- Account List ---\n");
    while (fread(&account, sizeof(Account), 1, file)) {
        printf("Account Number: %d\n", account.accountNumber);
        printf("Name: %s\n", account.name);
        printf("Balance: %.2f\n\n", account.balance);
    }
    fclose(file);
}

// Function to deposit money
void depositMoney() {
    FILE *file = fopen(DATA_FILE, "r+");
    Account account;
    int accNumber;
    double amount;
    int found = 0;

    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &accNumber);

    while (fread(&account, sizeof(Account), 1, file)) {
        if (account.accountNumber == accNumber) {
            printf("Enter amount to deposit: ");
            scanf("%lf", &amount);
            account.balance += amount;

            fseek(file, -sizeof(Account), SEEK_CUR);
            fwrite(&account, sizeof(Account), 1, file);
            printf("Deposit successful! New balance: %.2f\n", account.balance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(file);
}

// Function to withdraw money
void withdrawMoney() {
    FILE *file = fopen(DATA_FILE, "r+");
    Account account;
    int accNumber;
    double amount;
    int found = 0;

    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &accNumber);

    while (fread(&account, sizeof(Account), 1, file)) {
        if (account.accountNumber == accNumber) {
            printf("Enter amount to withdraw: ");
            scanf("%lf", &amount);
            if (amount > account.balance) {
                printf("Insufficient balance!\n");
            } else {
                account.balance -= amount;
                fseek(file, -sizeof(Account), SEEK_CUR);
                fwrite(&account, sizeof(Account), 1, file);
                printf("Withdrawal successful! New balance: %.2f\n", account.balance);
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(file);
}

// Function to check balance
void checkBalance() {
    FILE *file = fopen(DATA_FILE, "r");
    Account account;
    int accNumber;
    int found = 0;

    if (!file) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter account number: ");
    scanf("%d", &accNumber);

    while (fread(&account, sizeof(Account), 1, file)) {
        if (account.accountNumber == accNumber) {
            printf("Account Number: %d\n", account.accountNumber);
            printf("Name: %s\n", account.name);
            printf("Balance: %.2f\n", account.balance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(file);
}
