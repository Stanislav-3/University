#include <iostream>
#include <fstream>
using namespace std;

struct equipment{
    char name[30];
    char trademark[30];
    char date[15];
    char readiness[30];
};
equipment* structFill(char* filePath,equipment* peq);
equipment* equipmentP=0;

void show(equipment*);
void adddata(equipment*);
void deletedata(equipment*);
void changedata(equipment*);
void sort(equipment*);
void addad(equipment*);
int amount=0;

int main(int argc, const char * argv[]) {
    char *filePath="/Users/stanislav/Desktop/Лабораторные/Лабораторная 8/2/data.txt";
    equipmentP=structFill(filePath,equipmentP);
    int a=1;
    while(a){
        cout<<"0) End a programm\n1) See the info\n2) Add info\n3) Delete info\n4) Change info\n5) Sort by groups\n6) to add info without re-writing a file\n";
        cin>>a;
        switch(a){
            case 1: show(equipmentP);
                break;
            case 2: adddata(equipmentP);
                break;
            case 3: deletedata(equipmentP);
                break;
            case 4: changedata(equipmentP);
                break;
            case 5: sort(equipmentP);
                break;
            case 6: addad(equipmentP);
                break;
            default: if (a!=0)cout<<"Re-enter: \n";
        }
    }
//    Вывод файла result
    cout<<"Result file content:\n";
    ifstream fin;
    fin.open("/Users/stanislav/Desktop/Лабораторные/Лабораторная 8/2/result.txt");
//    while(!fin.eof()){
//        cout<<fin.get();
//    }
    string line;
    while(!fin.eof()){
        getline(fin,line);
        cout<<line<<endl;
    }
    fin.close();
    delete [] equipmentP;
    return 0;
}

equipment* structFill(char* filePath,equipment* obj){
    obj=new equipment[15];
    ifstream fin;
    fin.open(filePath,ios_base::in);
    if (fin.is_open()){}
    else{
        cout<<"File is not open\n";
    }
        int i=0;
        while(!fin.eof()){
            fin>>obj[i].name;
            fin>>obj[i].trademark;
            fin>>obj[i].date;
            fin.get();
            char buff[50];
            for(int j=0;j<50;j++)
                buff[j]='\0';
            fin.getline(buff,45);
            for(int j=0;buff[j]!='\0';j++)
                obj[i].readiness[j]=buff[j];
            amount++;
            i++;
        }
    fin.close();
    for(int i=0;i<amount;i++)
        if (obj[i].readiness[0] == 'R')
            strcpy(obj[i].readiness,"Ready");
        else if (obj[i].readiness[0] == 'N')
                 strcpy(obj[i].readiness,"Not ready");
//    запись в файл
    ofstream fout("/Users/stanislav/Desktop/Лабораторные/Лабораторная 8/2/result.txt");
    for(int i=0;i<amount;i++){
        fout<<obj[i].name<<' ';
        fout<<obj[i].trademark<<' ';
        fout<<obj[i].date<<' ';
        fout<<obj[i].readiness;
        if (i!=amount-1)
            fout<<'\n';
    }
    fout.close();
    return obj;
}
void show(equipment* obj){
    cout<<left<<"№"<<' '<<setw(12)<<"Name"<<setw(10)<<"Trademark"<<setw(12)<<"Date"<<"Readiness\n";
    for(int i=0;i<amount;i++){
    cout<<left<<i<<' '<<setw(12)<<obj[i].name<<setw(10)<<obj[i].trademark<<setw(12)<<obj[i].date<<obj[i].readiness<<endl;
    }
    cout<<endl;
}
void adddata(equipment* obj){
    int m=1;
    while(m){
        cout<<"Enter the data you want to add:\n";
        cout<<left<<setw(12)<<"Name"<<setw(10)<<"Trademark"<<setw(12)<<"Date"<<"Readiness\n";
        cin>>obj[amount].name;
        cin>>obj[amount].trademark;
        cin>>obj[amount].date;
        cin.ignore();
        gets(obj[amount].readiness);
        amount++;
        cout<<"One more?\n1-Yes\n0-No\n";
        cin>>m;
    }
    //    запись в файл
    ofstream fout("/Users/stanislav/Desktop/Лабораторные/Лабораторная 8/2/result.txt");
    for(int i=0;i<amount;i++){
        fout<<obj[i].name<<' ';
        fout<<obj[i].trademark<<' ';
        fout<<obj[i].date<<' ';
        fout<<obj[i].readiness;
        if (i!=amount-1)
            fout<<'\n';
    }
    fout.close();
}
void deletedata(equipment* obj){
    int m=1;
    while(m){
        show(obj);
        cout<<"What data to delete?: ";
        int d;
        cin>>d;
        for (int i=d;i<amount-1;i++)
            obj[i]=obj[i+1];
        amount--;
    cout<<"One more?\n1-Yes\n0-No\n";
        cin>>m;
    }
    //    запись в файл
    ofstream fout("/Users/stanislav/Desktop/Лабораторные/Лабораторная 8/2/result.txt");
    for(int i=0;i<amount;i++){
        fout<<obj[i].name<<' ';
        fout<<obj[i].trademark<<' ';
        fout<<obj[i].date<<' ';
        fout<<obj[i].readiness;
        if (i!=amount-1)
            fout<<'\n';
    }
    fout.close();
}
void changedata(equipment* obj){
    int m=1;
    while(m){
        show(obj);
        cout<<"What data to change?: ";
        int c;
        cin>>c;
        cin>>obj[c].name;
        cin>>obj[c].trademark;
        cin>>obj[c].date;
        cin.ignore();
        gets(obj[c].readiness);
    cout<<"One more?\n1-Yes\n0-No\n";
        cin>>m;
    }
    //    запись в файл
    ofstream fout("/Users/stanislav/Desktop/Лабораторные/Лабораторная 8/2/result.txt");
    for(int i=0;i<amount;i++){
        fout<<obj[i].name<<' ';
        fout<<obj[i].trademark<<' ';
        fout<<obj[i].date<<' ';
        fout<<obj[i].readiness;
        if (i!=amount-1)
            fout<<'\n';
    }
    fout.close();
}
void sort(equipment* obj){
    for (int i=0;i<amount;i++)
        for(int j=i+1;j<amount;j++){
            if (!strcmp(obj[i].name, obj[j].name)){
                equipment temp=obj[i+1];
                obj[i+1]=obj[j];
                obj[j]=temp;
                break;
            }
        }
    //    запись в файл
    ofstream fout("/Users/stanislav/Desktop/Лабораторные/Лабораторная 8/2/result.txt");
    for(int i=0;i<amount;i++){
        fout<<obj[i].name<<' ';
        fout<<obj[i].trademark<<' ';
        fout<<obj[i].date<<' ';
        fout<<obj[i].readiness;
        if (i!=amount-1)
            fout<<'\n';
    }
    fout.close();
}
void addad(equipment* obj){
    int m=1;
    while(m){
        cout<<"What info to add?\n";
        ofstream fout;
        fout.open("/Users/stanislav/Desktop/Лабораторные/Лабораторная 8/2/result.txt", ios_base::app);
        cout<<left<<setw(12)<<"Name"<<setw(10)<<"Trademark"<<setw(12)<<"Date"<<"Readiness\n";
        cin>>obj[amount].name;
        cin>>obj[amount].trademark;
        cin>>obj[amount].date;
        cin.ignore();
        gets(obj[amount].readiness);
        fout<<'\n'<<obj[amount].name<<' ';
        fout<<obj[amount].trademark<<' ';
        fout<<obj[amount].date<<' ';
        fout<<obj[amount].readiness;
        amount++;
        fout.close();
        cout<<"One more?\n1-Yes\n0-No\n";
        cin>>m;
    }
}
