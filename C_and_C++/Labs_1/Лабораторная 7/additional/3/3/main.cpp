#include <iostream>
using namespace std;
int main(int argc, const char * argv[]) {
    cout<<"Enter n: ";
    unsigned long int n;
    cin>>n;
//    перевод в 3-ичную
    int c=0;
    int num[100];
    for(int i=0;n>0;i++){
        num[i]=n%3;
        c++;
        n/=3;
    }
    for (int i=0;i<c/2;i++){
        int temp=num[i];
        num[i]=num[c-1-i];
        num[c-1-i]=temp;
    }
//    преобразование в троичную(123)
    for(int i=c-1;i>=0;i--){
        if(num[i]==0){
            num[i]=3;
            int j=i-1;
            for (;j>0;j--){
                if (num[j]==0){
                    num[j]=2;
                    i--;
                }
                else
                    break;
            }
            num[j]--;
            i--;
        }
    }
    for(int i=0;i<c;i++)
        if (num[i]==0){
            for(int j=i;j<c-1;j++)
                num[j]=num[j+1];
            c--;
        }
    for(int i=0;i<c;i++)
        cout<<num[i];
    cout<<endl;
    return 0;
}
 
