#include <stdio.h>
#include <string.h>
#include "Bank.h"

int loginAccount() {
    int accNo, pin;
    struct Account acc;

    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    if (searchAccount(accNo, &acc)) {
        printf("Enter PIN: ");
        scanf("%d", &pin);

        if (pin == acc.pin)
            return accNo;
    }

    printf("Login Failed!\n");
    return 0;
}

