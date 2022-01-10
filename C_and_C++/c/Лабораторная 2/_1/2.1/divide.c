#include <stdio.h>

/*
    Division of polynomials
 */
void definiteDivide(long double *polynomialDividendIndex, long double *polynomialDividerIndex) {
    long double dividendIndex[4], dividerIndex[4], quotient[4];
    int i = 0, j = -1, k = -1;
    for (; i < 4; i++) {
        dividendIndex[i] = polynomialDividendIndex[i];
        dividerIndex[i] = polynomialDividerIndex[i];
        quotient[i] = 0;
    }
    i = 0;
    /* Memorize the numbers (j, k) of the first index not equals to 0 (counting from the biggest position) */
    for (; i < 4; i++) {
        if ((j == -1) && (dividendIndex[i])) {
            j = i;
        }
        if ((k == -1) && (dividerIndex[i])) {
            k = i;
        }
    }
    if (k == -1) {
        printf("\nYou are not allowed to divide by 0!\n");
    } else if (j == -1) {
        printf("\nThe result of division is 0\n");
    } else {
        while ((j <= k) && (j != -1)) {
            /* tempIndex[4] will store current polynomial Index appeared after multiplication
             of the dividerand the current part of quotient */
            long double tempIndex[4] = {0, 0, 0, 0};
            int i = k;
            /* Current part of quotient */
            quotient[3 - (k - j)] = dividendIndex[j] / dividerIndex[k];
            for (; i < 4; i++) {
                tempIndex[i - k + j] = quotient[3 - (k - j)] * dividerIndex[i];
            }
            i = 0;
            /* After following loop dividendIndex will store a residue which if possible we divide by divider again */
            for (; i < 4; i++) {
                dividendIndex[i] -= tempIndex[i];
            }
            i=0;
            /* Update j value | If j == -1 residue == 0 */
            for(j = -1; i < 4; i++) {
                if ((j == -1) && (dividendIndex[i])) {
                    j = i;
                }
            }
        }
        printf("\nThe result of division: ");
        if (quotient[0]) {
            printf("%+Lgx^3", quotient[0]);
        }
        if (quotient[1]) {
            printf("%+Lgx^2", quotient[1]);
        }
        if (quotient[2]) {
            printf("%+Lgx", quotient[2]);
        }
        if (quotient[3]) {
            printf("%+Lg", quotient[3]);
        }
        if (!quotient[0] && !quotient[1] && !quotient[2] && !quotient[3]) {
            printf("0");
        }
        if ( j != -1) {
            printf("  (Residue: ");
            if (dividendIndex[0]) {
                printf("%+Lgx^3", dividendIndex[0]);
            }
            if (dividendIndex[1]) {
                printf("%+Lgx^2", dividendIndex[1]);
            }
            if (dividendIndex[2]) {
                printf("%+Lgx", dividendIndex[2]);
            }
            if (dividendIndex[3]) {
                printf("%+Lg)", dividendIndex[3]);
            }
        }
        printf("\n");
    }
    
}
/*
    Choose: divide 1/2 or 2/1
 */
void divide(long double *polynomial1Index, long double *polynomial2Index) {    
    short miniMenu;
    printf("\n1) First polynomial / second polynomial\n2) Second polynomial / first polynomial\nYour choice: ");
    scanf("%hd", &miniMenu);
    getchar();
    switch (miniMenu) {
        case 1:
        {
            definiteDivide(polynomial1Index, polynomial2Index);
            break;
        }
        case 2:
        {
            definiteDivide(polynomial2Index, polynomial1Index);
            break;
        }
        default:
            printf("\nThere were no such option\n");
    }
}
