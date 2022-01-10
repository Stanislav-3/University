/**
 * Variant 28
 * Restore the array ( all the elements below main diagonal equal to 0, others not equal 0),
 * from the mixed array
 */
#include <stdio.h>
#include <stdlib.h>

int DimensionInput(int *dimension) {
    char chNumber[2] = {0, 0};
    int i;
    for (i = 0; i <= 2; i++) {
        chNumber[i] = getchar();
        if (chNumber[i] == '\n') {
            chNumber[i] = 0;
            break;
        }
        if (i == 0) {
            if (chNumber[i] == '-') return 0;
            if (chNumber[i] == '+') {
                i = -1;
            }
        }
    }
    if (chNumber[1] != 0) return 0;
    if ((chNumber[0] < 48) && (chNumber[0] > 57)) return 0;
    *dimension = atoi(chNumber);
    return 1;
}

int ArrayInput(int ** array, int rows, int columns) {
    int i, j;
    printf("Input integer array elements:\n");
    for (i = 0; i < rows; i++) {
        if (i) {
            while(getchar() != '\n');
            
        }
        printf("Row №%d = ", i);
        for (j = 0; j < columns; j++) {
            /* Check if the input correct */
            int k;
            char chNumber[8] = {0, 0, 0, 0, 0, 0, 0, 0};
            scanf("%s", chNumber);
            if (chNumber[7] != 0) return 0;
            for (k = 0; k < 7; k++) {
                if (chNumber[k] == 0) break;
                if (((chNumber[k] < 48 || chNumber[k] > 57))) {
                    if((chNumber[k] != '+') && (chNumber[k] != '-') && (k == 0)) {
                        return 0;
                    } else if (k != 0) return 0;
                }
            }
            array[i][j] = atoi(chNumber);
        }
    }
    return 1;
}

int ArrayModify(int ** array, int rows, int columns) {
    /* Counter counts 0 */
    int i, j, counter;
    /* Swap rows */
    /* arr[i] stores number of 0 in i-row */
    int *arr = (int*)calloc(rows, sizeof(int));
    for (i = 0; i < rows; i++) {
        counter = 0;
        for (j = 0; j < columns; j++) {
            if (array[i][j] == 0) {
                counter++;
            }
        }
        arr[i] = counter;
    }
    /* Sort */
    for (i = 0; (i < rows) && (i < columns); i++) {
        if (i != arr[i]) {
            int *p;
            for (j = 0; j < rows; j++) {
                if (i == arr[j]) break;
            }
            if ((j == rows) && (arr[j] != i)) {
                return 0;
            }
            p = array[i];
            array[i] = array[j];
            array[j] = p;
            arr[j] = arr[i];
            arr[i] = i;
        }
    }
    free(arr);
    /* Swap columns */
    arr = (int*)calloc(columns, sizeof(int));
    /* arr[j] stores number of 0 in j-column */
    for (j = 0; j < columns; j++) {
        counter = 0;
        for (i = 0; i < rows; i++) {
            if (array[i][j] == 0) {
                counter++;
            }
        }
        arr[j] = counter;
    }
    /* Sort */
    for (j = 0; (j < columns) && (j < rows); j++) {
        if ((rows - 1 - j) != arr[j]) {
            int k;
            for (k = 0; k < columns; k++) {
                if ((rows - 1 - j) == arr[k]) break;
            }
            if ((k == columns) && (arr[k] != (rows - 1 - j))) {
                return 0;
            }
            for (i = 0; i < rows; i++) {
                int temp;
                temp = array[i][j];
                array[i][j] = array[i][k];
                array[i][k] = temp;
            }
            arr[k] = arr[j];
            arr[j] = (rows - 1 - j);
        }
    }
    free(arr);
    return 1;
}

int main(void) {
    int rows, columns, i, j;
    int **matrix = NULL;
    printf("Enter array dimensions (0 <= x <= 9):\nRows = ");
    if (!DimensionInput(&rows)) return -2;
    printf("Columns = ");
    if (!DimensionInput(&columns)) return -2;
    /* Creating dynamic array */
    matrix = (int**)calloc((unsigned long)rows, sizeof(int*));
    for (i = 0; i < rows; i++) {
        matrix[i] = (int*)calloc(columns, sizeof(int));
    }
    if(!ArrayInput(matrix, rows, columns)) {
        /* Delete dynamic array */
        for (i = 0; i < rows; i++) {
            free(matrix[i]);
        }
        free(matrix);
        return -1;
    }
    /* Not-modified array output */
    printf("The result matrix:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    if(ArrayModify(matrix, rows, columns)) {
        printf("The result matrix:\n");
        for (i = 0; i < rows; i++) {
            for (j = 0; j < columns; j++) {
                printf("%d ", matrix[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("The matrix cannot be restored...\n");
    }
    /* Delete dynamic array */
    for (i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}
