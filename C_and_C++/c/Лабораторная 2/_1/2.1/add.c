
#include <stdio.h>

/*
    Finds sum of polynomials
 */
void add(long double *polynomial1Index, long double *polynomial2Index) {
    printf("\nThe result: ");
    if (polynomial1Index[0] + polynomial2Index[0]) {
        printf("%+Lgx^3", polynomial1Index[0] + polynomial2Index[0]);
    }
    if (polynomial1Index[1] + polynomial2Index[1]) {
        printf("%+Lgx^2", polynomial1Index[1] + polynomial2Index[1]);
    }
    if (polynomial1Index[2] + polynomial2Index[2]) {
        printf("%+Lgx^1", polynomial1Index[2] + polynomial2Index[2]);
    }
    if (polynomial1Index[3] + polynomial2Index[3]) {
        printf("%+Lg", polynomial1Index[3] + polynomial2Index[3]);
    }
    printf("\n");
}
