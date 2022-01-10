#include <iostream>
#include <stdio.h>
using namespace std;
void shift(char*, int, int);
int main() {
    cout<<"Enter the text\n";
    char text[101];
    gets(text);
    for(int i=0; text[i] != '\0'; i++){
        if (text[i] == 'e' && text[i+1] == 'e'){
            shift(text,i,-1);
            text[i]='i';
        }
        if ((text[i] == 'y' || text[i] == 'y'-32) && text[i+1] == 'o' && text[i+2] == 'u'){
            shift(text, i, -2);
            if (isupper(text[i]))
                text[i]='U';
            else
                text[i]='u';
        }
        if (text[i] == 'o' && text[i+1] == 'o'){
            shift(text,i,-1);
            text[i]='u';
        }
        if ((text[i] == 't' || text[i] == 't'-32) && text[i+1] == 'h'){
            shift(text,i,-1);
            if (isupper(text[i]))
                text[i]='Z';
            else
                text[i]='z';
        }
        if ((text[i] == 'p' || text[i] == 'p'-32) && text[i+1] == 'h'){
            shift(text,i,-1);
            if (isupper(text[i]))
                text[i]='F';
            else
                text[i]='f';
        }
        if (text[i] == 'w' || text[i] == 'w'-32){
            if (isupper(text[i]))
                text[i]='V';
            else
                text[i]='v';
        }
        if (text[i] == 'x' || text[i] == 'x'-32){
            shift(text,i,1);
            if (isupper(text[i]))
                text[i]='K';
            else
                text[i]='k';
            text[i+1]='s';
        }
        if ((text[i] == 'q' || text[i] == 'q'-32) && text[i+1] == 'u'){
            if (isupper(text[i]))
                text[i]='K';
            else
                text[i]='k';
            text[i+1]='v';
        }
        if (text[i] == 'q' || text[i] == 'q'-32){
            if (isupper(text[i]))
                text[i]='K';
            else
                text[i]='k';
        }
        if (text[i] == 'c' || text[i] == 'c'-32){
            if(text[i+1] == 'e' || text[i+1] == 'i' || text[i+1] == 'y'){
               if (isupper(text[i]))
                   text[i]='S';
               else
                   text[i]='s';
            }
            else{
                if (isupper(text[i]))
                    text[i]='K';
                else
                    text[i]='k';
            }
        }
        if (((text[i] > 96 && text[i] <123) || (text[i] > 64 && text[i] <91)) && (text[i+1] == text[i] || text[i+1] == text[i]+32))
            shift(text, i, -1);
    }
    puts(text);
    return 0;
}
void shift(char* text, int i, int d){
    int len=strlen(text);
    if (d>0){
        for (int j=len+d-1; j>i+d; j--){
            text[j]=text[j-d];
        }
    }
    if (d<0){
        for(int j=i+1;j<len;j++){
            text[j]=text[j-d];
        }
    }
}
