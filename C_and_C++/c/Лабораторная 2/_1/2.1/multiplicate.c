#include <stdio.h>

/*
    Outputs multiplication of polynomials
 */
void multiplicate(long double *polynomial1Index, long double *polynomial2Index) {
    /* There will be stored indexes of product polynomial */
    long double resultPolynomialIndex[7] = {0, 0, 0, 0, 0, 0, 0};
    int i = 0;
    for (; i < 4; i++) {
        int j = 0;
        for (; j < 4; j++) {
            resultPolynomialIndex[i + j] += polynomial1Index[i] * polynomial2Index[j];
        }
    }
    printf("\nThe result of multiplication: ");
    /* Output variable with the coefficient only if they are not 0 */
    if (resultPolynomialIndex[0]) {
        printf("%+Lgx^6", resultPolynomialIndex[0]);
    }
    if (resultPolynomialIndex[1]) {
        printf("%+Lgx^5", resultPolynomialIndex[1]);
    }
    if (resultPolynomialIndex[2]) {
        printf("%+Lgx^4", resultPolynomialIndex[2]);
    }
    if (resultPolynomialIndex[3]) {
        printf("%+Lgx^3", resultPolynomialIndex[3]);
    }
    if (resultPolynomialIndex[4]) {
        printf("%+Lgx^2", resultPolynomialIndex[4]);
    }
    if (resultPolynomialIndex[5]) {
        printf("%+Lgx", resultPolynomialIndex[5]);
    }
    if (resultPolynomialIndex[6]) {
        printf("%+Lg", resultPolynomialIndex[6]);
    }
    printf("\n");
}
