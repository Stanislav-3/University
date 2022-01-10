
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
    Returns 0 if input is invalid, and 1 is evrething's correct
 */
short checkIntput(long double *polynomialIndex, short currentIndex) {
    char chNumber[326];
    long double ldNumber;
    short minus = 0, plus = 0;
    /* Point == 1 if there is a point in a number */
    short pointNumber = 0, i = 0;
    for (; i < 326; i++) {
        chNumber[i] = 0;
    }
    i=0;
    for(; i < 326; i++) {
        /* equal 1 if the input number is negative */
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
            /* Loop will continue executing from the index 0 again */
            if (chNumber[0] == '-') {
                minus++;
                i = -1;
                continue;
            }
            if(chNumber[0] == '+') {
                /* Loop will continue executing from the index 0 again */
                plus++;
                i = -1;
                continue;
            }
        }
        if ((plus == 1 && minus == 0) || (plus == 0 && minus == 1) || (plus == 0 && minus == 0)) {
            /* Chech if input is a number */
            if ((chNumber[i] < 48) || (chNumber[i] > 57)) {
                if ((chNumber[i] == '.') && (!pointNumber)) {
                    pointNumber++;
                }
                else {
                    printf("Invalid input...You should input a number\n");
                    return 0;
                }
            }
        }
        else {
            printf("Invalid input\n");
            return 0;
        }
    }
    ldNumber = atof(chNumber);
    if (ldNumber == INFINITY || ldNumber == -INFINITY) {
        printf("Invalid input...The number is too big");
        return 0;
    }
    if (minus == 1) {
        ldNumber *= -1;
    }
    polynomialIndex[currentIndex] = ldNumber;
    return 1;
}
/*
    Returns 0 if input is invalid and returns 1 if it's correct
 */
short input(long double *polynomial1Index, long double *polynomial2Index) {

    printf("\nTo process polynomials in the following form: ax^3+bx^2+cx+d intput polynomial coefficients a,b,c,d\n");
    /* getchar(); */
    printf("1 polynomial coefficients:\na = ");
    if(!checkIntput(polynomial1Index, 0)) {
        getchar();
        while (getchar() != '\n') {
        }
        return 0;
    }
    printf("b = ");
    if(!checkIntput(polynomial1Index, 1)) {
        getchar();
        while (getchar() != '\n') {
        }
        return 0;
    }
    printf("c = ");
    if(!checkIntput(polynomial1Index, 2)) {
        getchar();
        while (getchar() != '\n') {
        }
        return 0;
    }
    printf("d = ");
    if(!checkIntput(polynomial1Index, 3)) {
        getchar();
        while (getchar() != '\n') {
        }
        return 0;
    }
    printf("2 polynomial coefficients:\na = ");
        
    if(!checkIntput(polynomial2Index, 0)) {
        getchar();
        while (getchar() != '\n') {
        }
        return 0;
    }
    printf("b = ");
    if(!checkIntput(polynomial2Index, 1)) {
        getchar();
        while (getchar() != '\n') {
        }
        return 0;
    }
    printf("c = ");
    if(!checkIntput(polynomial2Index, 2)) {
        getchar();
        while (getchar() != '\n') {
        }
        return 0;
    }
    printf("d = ");
    if(!checkIntput(polynomial2Index, 3)) {
        getchar();
        while (getchar() != '\n') {
        }
        return 0;
    }
    return 1;
}
