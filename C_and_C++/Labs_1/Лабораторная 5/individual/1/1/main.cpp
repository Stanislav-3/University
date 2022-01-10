//1
#include <iostream>
#include "SLib.h"
int main(int argc, const char * argv[]) {
    int n;
    std::cout<<"Enter arrays dimension: ";
    std::cin>> n;
    int **A= new int  *[n];
    for (int i=0;i<n;i++)
        A[i]=new int [n];
    int **B= new int  *[n];
    for (int i=0;i<n;i++)
        B[i]=new int [n];
    arrA_initialization_and_output(A, n);
    std::cout<<"Sum of diagonal elements: "<<sum(A, n)<<"\n";
    arrB_initialization_and_output(B, n);
    std::cout<<"Sum of diagonal elements: "<<sum(B, n)<<"\n";
    for (int i=0;i<n;i++)
        delete [] A[i];
    for (int i=0;i<n;i++)
        delete [] B[i];
    return 0;
}
