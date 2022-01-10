#include <iostream>
using namespace std;
int pow(int, int);
void rec(int, int);
int main() {
    int p,q;
    cout<<"Из какой системы счисления хотите перевести? p:";
    cin>>p;
    cout<<"в какую? q:";
    cin>>q;
    cout<<"Введите число в "<<p<<"-ричной системе счисления:";
    cin.ignore();
    char num[10];
    int c=0,c2=0, num2=0, num0=0;
//    Заполнение массива(для решения с массивом) и подсчет реверснутой суммы(для решения без массива)
for (int i=0;;i++){
        char digit=cin.get();
        if (digit != '\n'){
            c2++;
            num[c]=digit;
            c++;
            if (digit >=48 && digit <=57){
                num0+=(digit-'0')*pow(p,i);
            }
            else
                num0+=(digit-'A'+10)*pow(p,i);
        }
        else
            break;
    }
    for (int i=0; c!=0 ; i++){
        if ((int)num[i]>=65 && (int)num[i]<=70){
            num2+=(num[i]-'A'+10)*pow(p, c-1);
        }
        else{
            num2+=(num[i]-'0')*pow(p, c-1);
        }
        c--;
    }
    int count=0;
    for(int i=0;num2 != 0;i++,count++){
        int digit= num2 % q;
        num2/=q;
        if (digit>=10 && digit<=15){
            num[i]=digit-10+'A';
        }
        else{
            num[i]=digit+'0';
        }
    }
    cout<<"C использованием массива:\n";
    for(int i=count-1;i>=0;i--){
        cout<<num[i];
    }
    cout<<"\n";
//БЕЗ МАССИВА
    cout<<"Без использования массива:\n";
    //    число в 10-ричной сс(реверс)
    int num3=0,i=0;
    while (num0 != 0){
        c2--;
        num3+=(num0/(int)pow(p,c2))*pow(p,i);
        num0-=(num0/(int)pow(p,c2))*pow(p,c2);
        i++;
    }
    rec(num3, q);
    cout<<endl;
    return 0;
}
int pow(int a, int b){
    if (b == 0)
        return 1;
    else
        return a*pow(a, b-1);
}
void rec(int x, int q){
    if (x!=0 && x>=q)
        rec(x/q, q);
    char digit = x%q;
    if (digit >=0 && digit <=9){
       cout<< (int)digit;
    }
    else
        cout<< (char)(digit+55);
}
