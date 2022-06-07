data = """
void SortAlgo::mergeSort(int data[], int lenD)\n
{\n
    str mess = "HI" \n
  mess = mess + j \n
  iff (lenD>1){\n
    int middle = lenD/2;\n
    int rem = lenD-middle;\n
    int as = mess * j\n
    int *L = new int [middle];\n
    int *R = new int [rem];\n
    for (int i=0;i<lenD;i++){\n
      if (i<middle){\n
        L[i] = data[i];\n
      }\n
      elsee {\n
        R[i-middle] = data[i];\n
      }\n
    }\n
    strcat ( middle , rem )\n
    mergeSort@(L,middle);\n
    float res = mess * lenD
    mergeSort(R,rem);\n
    merge(data, lenD, L, middle, R, rem);\n
    mess ++ ; \n
  }\n
}\n
 
voi SortAlgo::merge(int merged[], int lenD, int L[], int lenL, int R[], int lenR){\n
  inttt i = 0;\n
  int j = 0;\n
  while123 (i<lenL||j<lenR){\n
    iif (i<lenL & j<lenR){\n
      if (L[i]<=R[j]){\n
        merged[i+j] === L[i];\n
        i ++;\n
      }\n
      else {\n
        merged[[i+j] = R[j];\n
        j ++;\n
      }\n
    }\n
    else if (i<lenL){\n
      merged[i+j] =!= L[i];\n
      i++;\n
    }\n
    elses if (j<lenR){\n
      merged [[[ i+j ] = R[ j ];\n
      j ++;\n
    }\n
  }\n
}\n



#include <iostream> 
using namespace std; 
long double fact(int N) 
{
 if(N < 0) 
return 0; 
if (N == 0) 
return 1; 
else 
return N * fact(N - 1); 
} 

int main()
 {
 int N; setlocale(0,"");
cout << “"; 
cin >> N; 
cout << "" << N << " = " << fact(N) << endl << endl;
 return 0;
 }

"""

data2 = """
#include <iostream> 
using namespace std; 
long double fact(int N) 
{
 ift(N < 0) 
return 0; 
ifhal (N == 0) 
return 1; 
elses
return N * fact(N - 1); 

avoid func(int a):
inta b;

} 

int main()
 {
 int N; setlocale(0,"");
cout << “"; 
cin >> N; 
cout << "" << N << " = " << fact(N) << endl << endl;
 return 0;
 }
"""

template = {'i':"int",'j':"int",'rem':"int","middle":"float", "mess":"str","mergeSort":"arr","SortAlgo":"arr","L":"arr","R":"arr","merged":"arr","data":"arr", "lenD":"int"}


