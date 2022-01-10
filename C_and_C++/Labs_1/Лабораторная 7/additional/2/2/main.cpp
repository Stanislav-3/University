#include <iostream>
using namespace std;
int digits(int);
int pow(int,int);
int main(int argc, const char * argv[]) {
    int n;
    cout<<"Enter n: ";
    cin>>n;
    int k=1;
    for (int i=1;i<=n;){
        int num[100];
        for(;i<=n;k++){
            int c=0;
//            в двоичную сс(реверснутое)
            int kc=k;
            for(int j=0;kc>0;j++){
                num[j]=kc%2;
                c++;
                kc/=2;
            }
//            проверка на двудесятичность
            bool b=1;
            for (int j=0;j<digits(k);j++){
                if (num[j] != (k/(int)pow(10,j))%10){
                    b=false;
                    break;
                }
            }
            if (b==true)
                i++;
        }
    }
    cout<<k-1<<endl;
    return 0;
}
int digits(int a){
    int c=0;
    for(int i=0;a>0;i++){
        c++;
        a/=10;
    }
    return c;
}
int pow(int a, int q){
    if (q==0)
        return 1;
    int res=1;
    for(int i=0;i<q;i++)
        res*=a;
    return res;
}
