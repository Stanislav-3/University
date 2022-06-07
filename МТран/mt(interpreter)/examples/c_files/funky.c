void mergeSort(int data[], int lenD)
{
  char* mess = "HI";
  mess = mess + j;
  if (lenD>1){
    int middle = lenD/2;
    int rem = lenD-middle;
    int as = mess * j;
    int *L = data[middle];
    int *R = data[rem];
    for (int i=0;i<lenD;i++){
      if (i<middle){
        L[i] = data[i];
      }
      else {
        R[i-middle] = data[i];
      }
    }
    strcat(middle,rem);
    mergeSort(L,middle);
    float res = mess * lenD;
    mergeSort(R, rem);
    merge(data, lenD, L, middle, R, rem);
    mess ++ ;
  }
}
 
void merge(int merged[], int lenD, int L[], int lenL, int R[], int lenR)
{
  int i = 0;
  int j = 0;
  while (i<lenL||j<lenR){
    if (i<lenL & j<lenR){
      if (L[i]<=R[j]){
        merged[i+j] == L[i];
        i ++;
      }
      else {
        merged[i+j] = R[j];
        j ++;
      }
    }
    else if (i<lenL){
      merged[i+j] != L[i];
      i++;
    }
    else if (j<lenR){
      merged [ i+j ] = R[ j ];
      j ++;
    }
  }
}
