#include <iostream>
#include <stdio.h>
using namespace std;
unsigned long int bpow(unsigned long long int k,unsigned long long int n, int t){
if (n==0)
    return 1;
if (n%2 ==1)
    return bpow(k,n-1,t)*k%t;
else{
    unsigned long long int x=bpow(k,n/2,t)%t;
    return x*x;
}
}
int main(int argc, const char * argv[]) {
    int t;
    cout<<"Enter t: \n";
    cin>>t;
    unsigned long long int *a;
    a=new unsigned long long int[t];
    for (int i=0;i<t;i++)
        a[t]=0;
    for(int i=0;i<t;i++){
        char s1[201], s2[201];
        int m;
        unsigned long int l;
        cout<<"Enter l and m:\n";
        cin>>l>>m;
        cin.ignore();
        cout<<"Enter s1 and s2:\n";
        gets(s1);
        gets(s2);
        int l1=strlen(s1),l2=strlen(s2);
        int d=l-l1-l2;
        if (d>0){
            a[i]=2*bpow(26,d,m);
        }
        if (d<0){
            int count1=0, count2=0;
//                конец s1 совпадает с началом s2
            for(int j=0; s1[j] != '\0'; j++){
                if (s1[j] == s2[0]){
                    for(int k=0;s1[j+k] == s2[k];k++){
                        count1++;
                    }
                    if (j+count1 != l1){
                        count1=0;
                    }
                    else{
                        j=j+count1;
                    }
                }
            }
            if(d+count1 == 0)
                a[i]=1;
            
//                конец s2 совпадает с началом  s1
            for(int j=0; s2[j] != '\0'; j++){
                if (s2[j] == s1[0]){
                    for(int k=0;s2[j+k] == s1[k];k++){
                        count2++;
                    }
                    if (j+count2 != l2){
                        count2=0;
                    }
                    else{
                        j=j+count2;
                    }
                }
            }
            if(d+count2 == 0)
                a[i]=1;
            if (d+count2 == 0 && d+count1 == 0)
                a[i]=2;
        }
        
        if (d==0){
            a[i]=2;
        }
    }
    for (int i=0;i<t;i++)
        cout<<a[i]<<"\n";
    delete [] a;
    return 0;
}
