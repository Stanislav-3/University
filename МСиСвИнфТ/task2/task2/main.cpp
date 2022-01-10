/**
 *  Task 15
 *  В матрице A(10, 10) найти максимальные элементы в строках и максмимальный элемент матрицы.
 *  Вывести исходную матрицу, найденные значения элементов и номера строк и столбцов, где они находятся.
 */
#include <iostream>
#include <iomanip>
int main() {
    srand((unsigned int)time(nullptr));
    int matrix[10][10];
    // rowMaxElementJ[i] contains column number of the max element of i-row
    int rowMaxElementJ[10] = {0};
    // row & column of the max array element
    int maxElementI = 0, maxElementJ = 0;
    std::cout << "Matrix A(10, 10):\n";
    // Column number output
    for (int i = 0; i < 10; i++) {
        std::cout << std::setw(4) << "_№" << i;
    }
    std::cout << '\n';
    for (int i = 0; i < 10; i++) {
        std::cout<<"№"<<i<<'|';
        for (int j = 0; j < 10; j++) {
            // Matrix element initialization
            matrix[i][j] = rand() % 100;
            // Matrix element output
            std::cout << std::setw(3) << matrix[i][j];
            // Max row element search
            if (matrix[i][j] > matrix[i][rowMaxElementJ[i]]) {
                rowMaxElementJ[i] = j;
            }
        }
        // Max matrix element search
        if (matrix[i][rowMaxElementJ[i]] > matrix[maxElementI][maxElementJ]) {
            maxElementI = i;
            maxElementJ = rowMaxElementJ[i];
        }
        std::cout << '\n';
    }
    std::cout << '\n';
    // Max row element output
    for (int i = 0; i < 10; i++) {
        std::cout << "Row №"<< i << " Column №" << rowMaxElementJ[i] <<" Max:" << matrix[i][rowMaxElementJ[i]]<<"\n";
    }
    std::cout << '\n';
    // Max matrix element output
    std::cout << "Row №"<< maxElementI << " Column №" << maxElementJ <<" Max:" << matrix[maxElementI][maxElementJ]<<"\n";
    return 0;
}
