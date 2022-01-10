//  2
#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
void ioput(char *, char *, int &);
void shiftl(char *, int, int);
void shiftr(char *, int, int, int, int);
void fill(char*, char*, int, int, int);
int main() {
    char text1[500], text2[50];
    int len;
    ioput(text1, text2, len);
    int len2=strlen(text2);
    int i=0;
    while (text1[i] != '\0'){
        while (text1[i] == ' ')
            i++;
        int count=0;
        while (text1[i]!='\0' && text1[i] != ' '){
            count++;
            i++;
        }
        if (count==len){
            if (count == len2){
                int j=i-count,k=0;
                fill(text1, text2, len2, j, k);
            } else
            if (count >len2){
                int j=i-count,k=0;
                fill(text1, text2, len2, j, k);
                int s=count-len2;
                shiftl(text1, i, s);
                i-=s;
            } else
            if (count < len2){
                int len1=strlen(text1);
                shiftr(text1, len2, len1, count, i);
                int j=i-count,k=0;
                fill(text1, text2, len2, j, k);
            }
        }
    }
    puts(text1);
        return 0;
}
void ioput(char *text1, char *text2, int &len){
    cout<< "Enter the text:\n";
    gets(text1);
    cout<< "Enter the lengh of the word you'd like to replace: ";
    cin>> len;
    cout<<"Enter the string to replace with:\n";
    cin.ignore();
    gets(text2);
}
void shiftl(char* text1, int i, int s){
    while(text1[i-s]!='\0'){
        text1[i-s]=text1[i];
        i++;
    }
}
void shiftr(char* text1,int len2, int len1, int count, int i){
   int p=len1+len2-count;
    for(int j=p;j!=i;j--)
        text1[j]=text1[j-len2+count];
}
void fill(char* text1, char* text2,int len2,int j,int k){
    while(k<len2){
        text1[j]=text2[k];
        j++;
        k++;
    }
}
