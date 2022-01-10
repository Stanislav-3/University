#include <iostream>
using namespace std;
void tocomplementcode(int *, int);
void todirectcode(int *, int);
void shift(int*, int);
int main(int argc, const char * argv[]) {
    cout<<"Введите первое число в естественной форме a:";
    int a[8],ac=0;
    for(int i=0;i<8;i++)
        a[i]=0;
    for(int i=1;;i++){
        int d=cin.get();
        if (d!= '\n'){
            a[i]=d-'0';
            ac++;
        }
        else
            break;
        if (d== '-'){
            a[0]=1;
            i=0;
            ac--;
        }
        if (d== '+'){
            a[0]=0;
            i=0;
            ac--;
        }
    }
    cout<<"Введите второе число в естественной форме b:";
    int b[8],bc=0;
    for(int i=0;i<8;i++)
        b[i]=0;
    for(int i=1;;i++){
        int d=cin.get();
        if (d!= '\n'){
            b[i]=d-'0';
            bc++;
        }
        else
            break;
        if (d== '-'){
            b[0]=1;
            i=0;
            bc--;
        }
        if (d== '+'){
            b[0]=0;
            i=0;
            bc--;
        }
    }
    shift(a,ac);
    shift(b,bc);
    tocomplementcode(a, 8);
    tocomplementcode(b, 8);
    for(int i=0;i<8;i++)
        cout<<a[i];
    cout<<endl;
    for(int i=0;i<8;i++)
    cout<<b[i];
    int max=8;
//    if (ac>bc){
//        max=ac;
//        min=bc;
//        for(int i=max-1;i>=max-min;i--)
//            b[i]=b[i-(max-min)];
//        for(int i=0;i<max-min;i++)
//            b[i]=0;
//    }
//    else{
//        min=ac;
//        max=bc;
//        for(int i=max-1;i>=max-min;i--)
//            a[i]=a[i-(max-min)];
//        for(int i=0;i<max-min;i++)
//            a[i]=0;
//    }
    int s[max];
    for(int i=0;i<max;i++)
        s[i]=0;
    for (int i=0;i<=max;i++){
        s[max-1-i]=a[max-1-i]+b[max-1-i]+s[max-1-i];
        if(s[max-1-i] > 1){
            if(s[max-1-i] == 2)
                s[max-1-i]=0;
            if(s[max-1-i] == 3)
                s[max-1-i]=1;
            if(max-1-i != 0)
                s[max-2-i]=1;
        }
    }
    cout<<endl;
    for(int i=0;i<max;i++)
       cout<< s[i];
//    todirectcode(s, max);
    cout<<endl;
    //    перевод в обратный
    if(s[0]==1){
        if (s[max-1] == 1)
            s[max-1]=0;
        else{
            int i=2;
            s[max-1]=1;
            while(s[max-i]!=1){
                s[max-i]=1;
                i++;
            }
            s[max-i]=0;
        }
    //    перевод в прямой
        for(int i=1;i<max;i++){
            if (s[i] == 0)
                s[i]=1;
            else
                s[i]=0;
        }
        for (int i=0;i<max;i++){
            cout<<s[i];
        }
        cout<<endl;
    }
    return 0;
}
void tocomplementcode(int *a,int c){
    if(a[0] == 1){
        a[0]=0;
        c--;
        int t=-2;
        if(a[c] == 1){
            c--;
            t=0;
        }
        for(int i=c+t;i>=0;i--){
            a[i]=1-a[i];
        }
    }
    else
        return;
}
void shift(int *a,int c){
    int d=7-c;
    for (int i=7;i>d;i--)
        a[i]=a[i-d];
    for(int i=1;i<=d;i++)
        a[i]=0;
}
//void todirecrcode(int *a, int c){
////    перевод в обратный
//    if (a[c-1] == 1)
//        a[c-1]=0;
//    else{
//        int i=2;
//        a[c-1]=1;
//        while(a[c-i]!=1){
//            a[c-i]=1;
//            i++;
//        }
//        a[c-i]=0;
//    }
////    перевод в прямой
//    for(int i=1;i<c;i++){
//        a[i]=a[i]^a[i];
//    }
//    for (int i=0;i<c;i++){
//        cout<<a[i]<<' ';
//    }
//    cout<<endl;
//}
