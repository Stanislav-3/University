/*
    main.c
    Лабораторная 2
    2.1(16)
    Created by Stanislav Korenevsky on 2/18/20.
    Copyright © 2020 Stanislav Korenevsky. All rights reserved.
 */

#include <stdio.h>
#include "functions.h"
int atoi(const char *);
/**
 * Returns 0 if input is invalid otherwise returns 1
 */
short inputMenuCheck(short *item) {
    char chNumber[2] = {0, 0};
    char trash[256];
    int i = 0;
    for(; i < 2; i++) {
        chNumber[i] = getchar();
        if (chNumber[i] == '\n') {
            if (i == 0) {
                return 0;
            }
            chNumber[i] = 0;
            break;
        }
    }
    if ((chNumber[0] < 48 || chNumber[0] > 59) || (chNumber[1] != 0)) {
        /* Clear the input stream */
        for(i = 0; i < 255; i++) {
            scanf("%c", trash + i);
            if (trash[i] == '\n') {
                break;
            }
        }
        return 0;
    }
    *item = atoi(chNumber);
    return 1;
}

/*
    Prints menu, and memorize user's choice
 */
void menu(short attempt, short *item) {
   
    do {
        if (attempt) {
            printf("\n");
        }
        printf("Menu:\n");
        printf("0) Exit programm\n");
        printf("1) Input a two third-degree polynomials\n");
        /* Executes if user input polynomials */
        if (attempt > 0 ) {
            printf("2) Output polynomials\n");
            printf("3) Add polynomials\n");
            printf("4) Subtract polynomials\n");
            printf("5) Multiplicate polynomials\n");
            printf("6) Divide polynomials\n");
            printf("7) Information about programm version and developer\n");
        }
        else {
            printf("Other functions are temporary unavailable\n");
        }
        printf("Choice of the menu item: ");
        if (!inputMenuCheck(item)) {
            attempt = -1;
        } else {
            if (attempt == -1) {
                attempt = 0;
            }
        }
        /* Executes only if first user menu choice is invalid */
        if ((attempt == 0) && ((*item != 0) && (*item != 1))) {
            printf("\nInvalid input...Retry\n");
            attempt = -1;
        }
    } while(attempt == -1 || ((*item < 0) || (*item > 7)));
    /* Loop executes if user have chosen invalid menu item */
}

int main(void) {
    /*
        "item" is the menu item user has chosen
       "attempt" is 0 if it's the first time user uses the menu (otherwise 1)
     */
    short item, attempt=0;
    menu(attempt, &item);
    /* Loop executes unless user choose menu item №0 */
    for (;;) {
        /* There will be stored a,b,c,d of the polynomials a-[0] ... d-[3]*/
        long double polynomial1Index[4], polynomial2Index[4];
        switch (item) {
            case 0:
                return 0;
                break;
            case 1:
                if (input(polynomial1Index, polynomial2Index)) {
                    attempt++;
                }
                else {
                    attempt = 0;
                }
                break;
            
            case 2:
                output(polynomial1Index, polynomial2Index);
                break;
                
            case 3:
                add(polynomial1Index, polynomial2Index);
                break;
           case 4:
                subtract(polynomial1Index, polynomial2Index);
                break;
                
             case 5:
                multiplicate(polynomial1Index, polynomial2Index);
                break;
                
            case 6:
                divide(polynomial1Index, polynomial2Index);
                break;
                
            case 7:
                author();
                break;
                
            default:
                printf("Invalid input...Retry\n");
                break;
        }
        menu(attempt, &item);
    }
    return 0;
}
