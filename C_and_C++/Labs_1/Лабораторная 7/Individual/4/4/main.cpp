//15 ричная система
#include <iostream>
using namespace std;
void addition(char*,char*);
void substraction(char*,char*);
int len(char*);
void shiftr(char*,int,int);
void shiftl(char*);
int main() {
    cout<<"Введите два числа в 15-ричной системе :\n";
    char a[10], b[10],ac[10],bc[10];
    for(int i=0;i<10;i++){
        a[i]='\0';
        ac[i]='\0';
        b[i]='\0';
        bc[i]='\0';
    }
    for (int i=0;; i++){
        char temp=cin.get();
        if (temp == '+'){
            i--;
            continue;
        }
        if (temp != '\n'){
            a[i]=temp;
            ac[i]=temp;
        }
        else{
            a[i]='\0';
            ac[i]='\0';
            break;
        }
    }
    for (int i=0;; i++){
        char temp=cin.get();
        if (temp == '+'){
            i--;
            continue;
        }
        if (temp != '\n'){
            b[i]=temp;
            bc[i]=temp;
        }
        else{
            b[i]='\0';
            bc[i]='\0';
            break;
        }
    }
    cout<<"Результат сложения: ";
    if (a[0] != '-' && b[0] =='-'){
        shiftl(b);
        substraction(a, b);
    }
    else
        if (b[0] != '-' && a[0] =='-'){
            shiftl(a);
            substraction(b, a);
        }
        else
            addition(a, b);
    cout<<"\nРезультат вычитания: ";
    if (ac[0] == '-' && bc[0] =='-'){
        shiftl(bc);
        shiftl(ac);
        substraction(bc, ac);
    }
    else
        if (ac[0] == '-' && bc[0] !='-'){
            shiftl(ac);
            cout<<'-';
            addition(ac, bc);
        }
        else
            if (bc[0] == '-' && ac[0] !='-'){
                shiftl(bc);
                addition(ac, bc);
            }
            else
                substraction(ac, bc);
    cout<<endl;
    return 0;
}
void addition(char *a, char *b){
    int al=len(a), bl=len(b);
    if (al>bl)
        shiftr(b,al,bl);
    if (al<bl)
        shiftr(a,bl,al);
    int max;
    if (al>bl)
        max=al;
    else
        max=bl;
    if (a[0] == '-' && b[0] == '-'){
        for(int i=0;i<al;i++)
            a[i]=a[i+1];
        for(int i=0;i<bl;i++)
            b[i]=b[i+1];
        al--;
        bl--;
        max--;
        cout<<'-';
    }
    if (a[0] != '-' && b[0] != '-'){
        for(int i=0;a[i] != '\0';i++){
            if (a[i]>=48 && a[i]<=57){
                a[i]-='0';
            }
            else
                a[i]-='A'-10;
        }
        for(int i=0;b[i] != '\0';i++){
            if (b[i]>=48 && b[i]<=57){
                b[i]-='0';
            }
            else
                b[i]-='A'-10;
        }
        for(int i=1;i!=max+1;i++){
            a[max-i]+=b[max-i];
            if (a[max-i]>=15 && max-i != 0){
                a[max-i]-=15;
                a[max-i-1]+=1;
            }
            if (a[max-i]>=15 && max-i == 0){
                a[max-i]-=15;
                shiftr(a,max+1,max);
                a[max-i]=1;
                max+=1;
                break;
            }
        }
    }
    for(int i=0; i<max;i++)
        if (a[i]<=9){
            cout<<(int)a[i];
        }
        else{
            cout<<(char)(a[i]-10+'A');
        }
}
void substraction(char *a, char *b){
    int al=len(a), bl=len(b);
    if (al>bl)
        shiftr(b,al,bl);
    if (al<bl)
        shiftr(a,bl,al);
    int max;
    if (al>bl)
        max=al;
    else
        max=bl;
    if (a[0]!='-' && b[0] != '-'){
        for(int i=0;i<max;i++){
            if (a[i]>=48 && a[i]<=57){
                a[i]-='0';
            }
            else
                a[i]-='A'-10;
        }
        for(int i=0;b[i]!='\0';i++){
            if (b[i]>=48 && b[i]<=57){
                b[i]-='0';
            }
            else
                b[i]-='A'-10;
            }
//          если вычитаемое больше
        bool bigger=1;
        for(int i=0;i<max;i++){
            if (a[i]<b[i]){
                bigger=0;
                break;
            }
            if (a[i]>b[i]){
                break;
            }
        }
        if (bigger==false){
            cout<<'-';
            for (int i=0;i<max;i++){
                char temp=a[i];
                a[i]=b[i];
                b[i]=temp;
            }
        }
        for(int i=1;i!=max+1;i++){
            if (a[max-i]>=b[max-i])
                a[max-i]-=b[max-i];
            else{
                a[max-i]=a[max-i]+15-b[max-i];
                a[max-i-1]--;
                for(int j=max-i-1;a[j]==0 && j>0;j--){
                    a[j]=14;
                    if(a[j-1]!=0)
                        a[j-1]--;
                }
            }
        }
        int j=0;
        for(int i=0;i<max-1+j && a[i]=='\0';i++){
            for(;j<max-1;j++){
                a[j]=a[j+1];
            }
            max--;
        }
            for(int i=0; i<max;i++)
            if (a[i]<=9)
                cout<<(int)a[i];
            else
                cout<<(char)(a[i]-10+'A');
    }
}
int len(char *a){
    int i=0;
    while (a[i] != '\0')
        i++;
    return i;
}
void shiftr(char *a,int max, int min){
    int d=max-min;
    for (int i=max-1;i>=d;i--)
        a[i]=a[i-d];
    for(int i=0;i<d;i++)
        a[i]='0';
}
void shiftl(char *text){
    int len=0;
    for(int k=0;text[k] != '\0';k++)
        len++;
    for(int k=0;k<len;k++)
        text[k]=text[k+1];
}
