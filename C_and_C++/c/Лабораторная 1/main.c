/*
    Лабораторная 1
    1.2(16)
    Created by Stanislav Korenevsky on 2/15/20.
    Copyright © 2020 Stanislav Korenevsky. All rights reserved.
*/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/*
    Function returns an input value if the input is correct,
    else - outputs corresponding message and returns 0
*/
int input(void) {
    
    printf("Input a natural number\nYour number (INS): ");
    char chNumber[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    short plusCounter = 0;
    int i = 0;
    for(; i < 8; i++) {
        chNumber[i] = getchar();
        if (chNumber[i] == '\n') {
            if (i == 0) {
                printf("Invalid input...You didn't enter enything\n");
                return 0;
            }
            chNumber[i] = 0;
            break;
        }
        /* Check the signes */
        if (i == 0) {
            if (chNumber[0] == '-') {
                printf("Invalid input...There was no negative numbers\n");
                return 0;
            }
            if(chNumber[0] == '+') {
                /* Loop will continue executing from the index 0 again */
                i = -1;
                plusCounter++;
                continue;
            }
        }
        if (plusCounter > 1) {
            printf("Invalid input...You should input a natural number\n");
            return 0;
        }
        /* Chech if input is a number */
        if ((chNumber[i] < 48) || (chNumber[i] > 57)) {
            printf("Invalid input...You should input a natural number\n");
            return 0;
        }
    }
    /* Check for overflow */
    if (chNumber[7] != 0) {
        printf("Invalid input...You should input a natural number < 4 000 000\n");
        return 0;
    }
    int intNumber = atoi(chNumber);
    if (intNumber >= 4000000) {
        printf("Invalid input!\nThere was no use in such big numbers in that time so "
        "a number should be smaller than 4 000 000\n");
        return 0;
    } else if (!intNumber) {
        printf("There wasn't 0 in RNS (They thought in following way: Why do want to count nothing?)\n");
        return 0;
    }
      else {
        return intNumber;
    }
}
/*
    Translate digit from ANS into RNS taking into account a position of each digit
    Position is a place of a digit in the number (counting from right to left strating with 0)
*/
 void digitTranslate(int digit, int position) {
    
    char romanDigits[13][4] = {"Ⅰ", "Ⅴ", "Ⅹ", "Ⅼ", "Ⅽ", "Ⅾ", "Ⅿ", "V̅", "X̅", "L̅", "C̅", "D̅", "M̅"};
    if (digit == 5) {
        printf("%s", romanDigits[1 + 2 * position]);
    } else if (digit == 4) {
        printf("%s", romanDigits[0 + 2 * position]);
        printf("%s", romanDigits[1 + 2 * position]);
    } else if (digit == 6) {
        printf("%s", romanDigits[1 + 2 * position]);
        printf("%s", romanDigits[0 + 2 * position]);
        
    } else if (digit == 9) {
        printf("%s", romanDigits[0 + 2 * position]);
        printf("%s", romanDigits[2 + 2 * position]);
    } else if ((digit > 0) && (digit < 4)) {
        for(; digit > 0; digit--) {
                printf("%s", romanDigits[0 + 2 * position]);
        }
    } else if ((digit > 6) && (digit < 9)) {
        printf("%s", romanDigits[1 + 2 * position]);
        for(digit -= 5; digit > 0; digit--) {
                printf("%s", romanDigits[0 + 2 * position]);
        }
    }
}
/*
    Function extracts digits of a number starting from the biggest position
    and pass them as an argument to function "digitTranslate"
*/
 void extractAndTranslateDigit(int number) {
    
    /* Count digits */
    int digitsNumber = 0;
    for (; (int)(number / (pow(10, digitsNumber))); digitsNumber++) {}
    printf("Your number (RNS): ");
    /* Translate number into RNS */
    for(; digitsNumber; digitsNumber--) {
        digitTranslate((number / (int)pow(10, digitsNumber - 1)) % 10, digitsNumber - 1);
    }
    printf("\n");
}

int main(void) {
    
    int number = 0;
    printf("This program translates numbers from Indian Numeral System (INS) into Roman Numeral System (RNS)\n");
    number = input();
    if (number) {
        extractAndTranslateDigit(number);
    }
    return 0;
}
