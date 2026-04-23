#include <stdio.h>
#include <unistd.h>
#include "Bank.h"

#define CYAN   "\033[1;36m"
#define GREEN  "\033[1;32m"
#define YELLOW "\x1b[33m"
#define RESET  "\033[0m"

void loading() {
    printf(GREEN "\n\nInitializing Secure Banking System");
    fflush(stdout);

    for(int i = 0; i < 5; i++) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    printf(RESET "\n");
}

void showArt() {
    printf(YELLOW);
    printf(
"   _____________________\n"
"  |                     |\n"
"  |   BANK MANAGEMENT   |\n"
"  |_____________________|\n"
"        ||       ||\n"
"        ||       ||\n"
"      __||_______||__\n"
"     |               |\n"
"     |      $$$      |\n"
"     |_______________|\n"
    );
    printf(RESET);
}

void showTitle() {
    printf("\n");
    printf("=====================================================\n");
    printf("                 BANK MANAGEMENT SYSTEM              \n");
    printf("=====================================================\n");
}

void showMenu() {
    printf("\n=====================================\n");
    printf("               MAIN MENU             \n");
    printf("=====================================\n");
    printf("1. Create New Account\n");
    printf("2. Customer Login\n");
    printf("3. Exit\n");
    printf("=====================================\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;


    showArt();
    showTitle();
    loading();

    printf("\nWelcome to Secure Banking Interface\n");
    printf("Press Enter to continue...");
    getchar();

    do {
        showMenu();
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                createAccount();
                printf("\n[Create Account Module Coming Soon]\n");
                break;

             case 2: { 
                int loggedInAccNo = loginAccount(); 
                
                if (loggedInAccNo != 0) { 
                    struct Account currentUser;
                    
                    
                    if (searchAccount(loggedInAccNo, &currentUser)) { 
                        
                        
                        showTransactionMenu(&currentUser); 
                    }
                } else {
                    
                }
                break;
            }
            case 3:
                printf("\nThank you for using our bank!\n");
                break;

            default:
                printf("\nInvalid choice. Try again.\n");
        }

    } while(choice != 3);

    return 0;
}