#include <stdio.h>
#include "Bank.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

int generateAccountNumber() {
    int r;
    struct Account temp;
    do {
        r = rand() % 900000 + 100000;
    } while (searchAccount(r, &temp)); 
    return r;
}

void updateCSV(struct Account *updatedAcc) {
    FILE *file = fopen("Data.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    struct Account tempAcc;
    int found = 0;

    // Check if files opened successfully
    if (file == NULL || temp == NULL) {
        printf("\033[31mError: Could not open database files!\033[0m\n");
        return;
    }

    // Read the original file line by line
    while (fscanf(file, "%d,%49[^,],%d,%99[^,],%19[^,],%f,%d\n",
            &tempAcc.accountNumber, tempAcc.name, &tempAcc.age,
            tempAcc.address, tempAcc.type, &tempAcc.balance, &tempAcc.pin) == 7) {
        
        // If we hit the account we just modified in transaction.c...
        if (tempAcc.accountNumber == updatedAcc->accountNumber) {
            // Write the UPDATED struct data to the temp file
            fprintf(temp, "%d,%s,%d,%s,%s,%.2f,%d\n",
                    updatedAcc->accountNumber, updatedAcc->name, updatedAcc->age,
                    updatedAcc->address, updatedAcc->type, updatedAcc->balance, updatedAcc->pin);
            found = 1;
        } else {
            // Otherwise, copy the old data exactly as it was
            fprintf(temp, "%d,%s,%d,%s,%s,%.2f,%d\n",
                    tempAcc.accountNumber, tempAcc.name, tempAcc.age,
                    tempAcc.address, tempAcc.type, tempAcc.balance, tempAcc.pin);
        }
    }

    // Close both files to release them from memory
    fclose(file);
    fclose(temp);

    // Replace the old file with the new one
    if (found) {
        remove("Data.csv");           // Delete original
        rename("temp.csv", "Data.csv"); // Rename temp to Data.csv
    } else {
        remove("temp.csv"); // Clean up the temp file if the account wasn't found
    }
}
void createAccount() {
    struct Account acc;
    FILE *file;

    acc.accountNumber = generateAccountNumber();

    printf("\nEnter your name: ");
    scanf("%s", acc.name);

    printf("Enter your age: ");
    scanf("%d", &acc.age);

    printf("Enter Address: ");
    scanf(" %[^\n]", acc.address);

    printf("Enter Account Type (Savings/Current): ");
    scanf("%s", acc.type);

    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    printf("Set 4-digit PIN: ");
    scanf("%d", &acc.pin);

    file = fopen("Data.csv", "a");
    
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return; 
    }

    // FIXED: Added the PIN formatting (%d) and the acc.pin variable to the end
    fprintf(file, "%d,%s,%d,%s,%s,%.2f,%d\n", 
            acc.accountNumber, 
            acc.name, 
            acc.age, 
            acc.address, 
            acc.type, 
            acc.balance,
            acc.pin); 

    printf("\nSuccess! Account %d has been created and saved to Data.csv.\n", acc.accountNumber);

    fclose(file);
}


int searchAccount(int accNo, struct Account *acc) {
    FILE *file = fopen("Data.csv", "r");
    if (file == NULL) return 0;

    while (fscanf(file, "%d,%49[^,],%d,%99[^,],%19[^,],%f,%d\n",
            &acc->accountNumber, acc->name, &acc->age,
            acc->address, acc->type, &acc->balance, &acc->pin) == 7) {
        if (acc->accountNumber == accNo) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

