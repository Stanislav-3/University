#include <iostream>
using namespace std;
unsigned long int fact(int a){
    if (a==1)
        return 1;
    else
        return a*fact(a-1);
}
int main() {
    char word[15];
    int k[14]={1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    cin>> word;
    for(int i=0; word[i]!='\0';i++){
        for (int j=0;word[j]!='\0';j++){
            if (word[i] < word[j]){
                char temp=word[j];
                word[j]=word[i];
                word[i]=temp;
            }
        }
    }
    int j=0;
    for(int i=0; word[i]!='\0';i++){
        while(word[i] == word[i+1]){
            k[j]++;
            i++;
        }
        j++;
    }
    unsigned long int num = fact(strlen(word));
    for (int i=0;i<14;i++){
        num/=fact(k[i]);
    }
    cout<< num;
    return 0;
}
