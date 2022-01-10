#include <iostream>
#include <iomanip>
void arrB_initialization_and_output(int **B, int n){
    for (int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            B[i][j]=2*i*(j-2);
            std::cout<<std::setw(3)<<std::left<<B[i][j]<<" ";
        }
    std::cout<<"\n";
    }
}

