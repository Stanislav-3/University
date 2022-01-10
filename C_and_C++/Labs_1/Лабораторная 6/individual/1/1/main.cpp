//2
#include <iostream>
#include <stdio.h>
using namespace std;
void counter(char *, int &, int &);
void output(char *, int, int, bool);
int main() {
    char text[81];
    gets(text);
    int i=0, remember=-1, min=80;
    bool m=false;
    while(text[i]!='\0'){
        int c=1;
        counter(text, i, c);
        if(c==min)
            m=false;
        else
        if (c < min && c!=1){
            remember=i;
            min=c;
            m=true;
        }
        i++;
    }
    output(text, remember, min, m);
    return 0;
}
void counter(char *text,int &i,int &c){
    while(text[i]==text[i+1]){
        c++;
        i++;
    }
}
void output(char *text, int remember,int min, bool m){
    if (m==true)
        for (int j=remember-min+1;j<=remember;j++)
            cout << (text[j])<<" ";
    else
        cout<<"There's no minimum group\n";
}
