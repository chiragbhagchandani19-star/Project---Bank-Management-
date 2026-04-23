#include <stdio.h>
#include <stdlib.h>
#include "Bank.h" 

#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"

void print_header() {
    printf(CYAN);
    printf(" ___________________________\n");
    printf("|  _______________________  |\n");
    printf("| |  " BOLD "TRANSACTION SYSTEM" RESET CYAN "   | |\n");
    printf("| |_______________________| |\n");
    printf("|___________________________|\n" RESET);
}


void showTransactionMenu(struct Account *acc) {
    int choice;
    float amount; 
    
    do {
        system("clear || cls"); 
        print_header();

        printf("\n" BOLD "WELCOME, %s!\n" RESET, acc->name);
        printf(BOLD "BALANCE: " GREEN "%.2f\n" RESET, acc->balance);
        printf("-----------------------------\n");
        printf("1) " YELLOW "Deposit\n" RESET);
        printf("2) " YELLOW "Withdraw\n" RESET);
        printf("3) " YELLOW "Transfer\n" RESET);
        printf("4) " RED "Exit\n" RESET);
        printf("-----------------------------\n");
        printf("Select: ");
        
        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n'); 
            continue;
        }

        printf("\n");

        switch(choice) {
            case 1:
                printf("Amount to deposit: ");
                scanf("%f", &amount);
                acc->balance += amount;  
                
                updateCSV(acc); 
                
                printf(GREEN "Success! New Balance: %.2f\n" RESET, acc->balance);
                break;

            case 2:
                printf("Amount to withdraw: ");
                scanf("%f", &amount);
                if(acc->balance >= amount) {
                    acc->balance -= amount; 
                    
                    updateCSV(acc);         
                    
                    printf(GREEN "Success! New Balance: %.2f\n" RESET, acc->balance);
                } else {
                    printf(RED "Error: Insufficient funds.\n" RESET);
                }
                break;

            case 3: { 
                int targetAccNo;
                struct Account targetAcc;
                
                printf("Enter destination Account Number: ");
                scanf("%d", &targetAccNo);
                
                // 1. Check if the destination account exists and load its data
                if (searchAccount(targetAccNo, &targetAcc)) {
                    
                    // Prevent transferring money to themselves
                    if (targetAccNo == acc->accountNumber) {
                        printf(RED "Error: Cannot transfer to your own account.\n" RESET);
                        break;
                    }

                    printf("Amount to transfer: ");
                    scanf("%f", &amount); // Using %f since we changed amount to float!
                    
                    // 2. Check if the amount is valid and sender has enough money
                    if (amount > 0 && acc->balance >= amount) {
                        
                        // 3. Deduct from sender and update CSV
                        acc->balance -= amount; 
                        updateCSV(acc); 
                        
                        // 4. Add to receiver and update CSV
                        targetAcc.balance += amount;
                        updateCSV(&targetAcc);
                        
                        printf(GREEN "Success! Transferred %.2f to %s.\n" RESET, amount, targetAcc.name);
                        printf("Your New Balance: %.2f\n", acc->balance);
                    } else {
                        printf(RED "Error: Insufficient funds or invalid amount.\n" RESET);
                    }
                } else {
                    printf(RED "Error: Destination account not found.\n" RESET);
                }
                break;
            }

            case 4:
                printf(CYAN "Returning to main menu...\n" RESET);
                break;

            default:
                printf(RED "Invalid choice.\n" RESET);
        }

        if (choice != 4) {
            printf("\nPress Enter to continue...");
            while(getchar() != '\n'); 
            getchar(); 
        }

    } while(choice != 4); 
}