#include <iostream>
#include <stdio.h>
using namespace std;
void shift(char*, int, int);
int main(int argc, const char * argv[]) {
    const int n=3;
    char ch[n][101];
    for (int i=0; i<n; i++)
        for (int j=0; j<100; j++){
            ch[i][j]=cin.get();
            if (ch[i][j]=='\n'){
                ch[i][j]='\0';
                break;
            }
        }
    for (int i=0; i<n; i++){
        int j=0;
        while (ch[i][j] != '\0'){
            int count =1;
            while (ch[i][j] == ch[i][j+1]){
                count++;
                j++;
            }
            if (count!=1){
                ch[i][j-count+1] = 32;
//                нахождение цифр кода
                int codelen=0, code=(int)ch[i][j], codedijits[3]={0, 0, 0};
                for(int y=0; code!=0; y++){
                    codedijits[y]=code%10;
                    code/=10;
                    codelen++;
                }
//                нахождение цифр количества числа
                int countlen=0, countdigits[3]={0, 0, 0};
                int countcopy=count;
                for(int y=0; countcopy!=0; y++){
                    countdigits[y]=countcopy%10;
                    countcopy/=10;
                    countlen++;
                }
                shift(ch[i], j, count-codelen-countlen-1);
                for (int x=0;x<codelen;x++)
                    ch[i][j-count+2+x]=codedijits[codelen-x-1]+'0';
                for (int x=0;x<countlen;x++)
                    ch[i][j-count+2+x+codelen]=countdigits[countlen-x-1]+'0';
                j=j-(count-codelen-countlen)+1;

            }
            j++;
        }
    }
    for(int i=0; i<n; i++){
        for (int j=0; j<100 && ch[i][j]!='\0'; j++)
            cout<<ch[i][j];
        cout<<endl;
    }
    return 0;
}
void shift(char *text, int i, int d){
    int len=0;
    for(int k=0;text[k] != '\0';k++)
        len++;
    if (d>0){
        for (int j=i-d+1; j<len; j++){
            text[j]=text[j+d];
        }
    }
    if (d<0){
        for(int j=len-d;j>i-d;j--){
            text[j]=text[j+d];
        }
    }
    if (d == 0)
        return;
}

