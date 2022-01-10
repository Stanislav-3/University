#include <iostream>
#include <iomanip>
void arrA_initialization_and_output(int **A, int n){
    for (int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            A[i][j]=3*i*(j-3);
            std::cout<<std::setw(3)<<std::left<<A[i][j]<<" ";
        }
    std::cout<<"\n";
    }
}
