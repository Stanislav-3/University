
#include <stdio.h>

void add(long double *polynomial1Index, long double *polynomial2Index);

/*
    Changes the sign of coefficients of polynomial to the opposite
 */
void reverse(long double *polynomialIndex) {
    short i = 0;
    for (; i < 4; i++) {
        polynomialIndex[i] = -1 * polynomialIndex[i];
    }
}

/*
    Outputs the difference of polynomials
 */
void subtract(long double *polynomial1Index, long double *polynomial2Index) {
    short miniMenu;
    printf("\n1) First polynomial - second polynomial\n2) Second polynomial - first polynomial\nYour choice: ");
    scanf("%hd", &miniMenu);
    getchar();
    switch (miniMenu) {
        case 1:
        {
            reverse(polynomial2Index);
            add(polynomial1Index, polynomial2Index);
            reverse(polynomial2Index);
            break;
        }
        case 2:
        {
            reverse(polynomial1Index);
            add(polynomial1Index, polynomial2Index);
            reverse(polynomial1Index);
            break;
        }
        default:
            printf("\nThere were no such option\n");
    }
}
