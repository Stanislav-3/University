#include <stdio.h>
#include <math.h>
#include <stdlib.h>
/*
 The programm compare values of sin(x) counted using library function and using math expansion.
 */
const double E = 0.001;

short checkIntput(long double *variable) {
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
    if (ldNumber < -1000000000 || ldNumber > 1000000000) {
        printf("The number is too big...\n");
        return 0;
    }
    if(ldNumber > 30){
        int i;
        for(i = 0; ldNumber > 25; i++) {
            ldNumber -= 2 * M_PI;
        }
    }
    if(ldNumber < 30){
        int i;
        for(i = 0; ldNumber < 25; i++) {
            ldNumber += 2 * M_PI;
        }
    }
    if (ldNumber == INFINITY || ldNumber == -INFINITY) {
        printf("Invalid input...The number is too big");
        return 0;
    }
    if (minus == 1) {
        ldNumber *= -1;
    }
    *variable = ldNumber;
    return 1;
}

void iterativeFunction(double x) {
    int n = 0;
    double sum = 0;
    do {
        int i = 1;
        long double term = 1;
        n++;
        for(; i <= 2 * n - 1; i++) {
            term *= x / i;
        }
        if (n % 2 == 0) {
            term *= -1;
        }
        sum += term;
    } while (fabs(sin(x) - sum) > E);
    printf("%f (n = %d)", sum, n);
    
}

void recursiveFunction(double x, int n, double sum) {
    int i = 1;
    double term = 1;
    for(; i <= 2 * n - 1; i++) {
        term *= x / i;
    }
    if (n % 2 == 0) {
        term *= -1;
    }
    sum += term;
    if (fabs(sin(x) - sum) > E) {
        recursiveFunction(x, n + 1, sum);
    }
    else {
        printf("%f (n = %d)\n", sum, n);
    }
}

int main(void) {

    int mark = 0;
    long double x;
    printf("Input x: ");
    mark = checkIntput(&x);
    if (mark) {
        printf("Sin(x) counted using library function: %f", sin(x));
        printf("\nSin(x) counted using math expansion (Accuracy: E = %g):\n1) Iterative function: ", E);
        iterativeFunction(x);
        printf("\n2) Recursive function: ");
        recursiveFunction(x, 1, 0);
    }
    return 0;
}
