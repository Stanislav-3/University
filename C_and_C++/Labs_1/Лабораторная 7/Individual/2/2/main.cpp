#include <iostream>
using namespace std;
int main(){
    cout<<"Введите дополнительный код: ";
    unsigned long int a[8];
    int c=0;
    for(int i=0;;i++){
        int d=cin.get();
        if (d!= '\n'){
            a[i]=d-'0';
            c++;
        }
        else
            break;
    }
    if (a[c-1] == 1)
        a[c-1]=0;
    else{
        int i=2;
        a[c-1]=1;
        while(a[c-i]!=1){
            a[c-i]=1;
            i++;
        }
        a[c-i]=0;
    }
    cout<<"Обратный код:\n";
    for(int i=0;i<c;i++)
        cout<<a[i];
    cout<<endl;
    return 0;
}
