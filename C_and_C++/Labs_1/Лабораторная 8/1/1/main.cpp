#include <iostream>
#include <iomanip>
using namespace std;
#include <cstdlib>
#include <string>
#include <complex>
struct product{
    int number;
    char name[20];
    int amount;
    float value;
    char date[11];
};

product* pProduct=0;
int ProductAmount=0;
int YesOrNot=0;

product* addstruct(product* obj, int amount);
void fillstruct(product*, int);
void show(product* obj, int amount);
void search(product* obj, int amount);
void change(product* obj, int amount);
void sort(product* obj, int amount);
void changestruct(product* obj, int amount);

int main() {
    cout<<left<<setw(4)<<"№"<<setw(5)<<"Name"<<setw(7)<<"Amount"<<setw(6)<<"Value"<<setw(5)<<"Date\n";
label:do{
        
        
        pProduct=addstruct(pProduct,ProductAmount);
        fillstruct(pProduct,ProductAmount);
        ProductAmount++;
        
        cout<<"Enter 0 to stop & 1 to continue: ";
        cin>>YesOrNot;
        cout<<endl;
//        cin.get();
    }while(YesOrNot != 0);
 menu:   int cases;
cout<<"\nEnter:\n 1 -to see all info\n 2 -to search info\n 3 -to delete or change any struct alement\n 4 -to delete or change any struct\n 5 -add a new struct\n 6 -sort(by value)\n 7 -end a programm\n";
    cin>>cases;
    if (cases==1)
        show(pProduct,ProductAmount);
    if (cases==2)
        search(pProduct,ProductAmount);
    if (cases==3)
        change(pProduct,ProductAmount);
    if (cases==4)
        changestruct(pProduct,ProductAmount);
    if (cases==5)
        goto label;
    if (cases==6)
        sort(pProduct,ProductAmount);
    if(cases==7){
        cout<<endl;
        return 0;
    }
    goto menu;
    
}
product* addstruct(product* obj, int amount){
    
    if (amount == 0){
        obj= new product[amount+1];
    }
    else{
        product* tempObj= new product[amount+1];
        for (int i=0;i<amount;i++){
            tempObj[i]=obj[i];
        }
        delete [] obj;
        obj=tempObj;
        
    }
    
    return obj;
}

void fillstruct(product* obj,int num){
    cout<<"№:"<<num<<endl;
    if(num != 0){
        cout<<"Enter 1 to type info & enter 2 to copy info: ";
        int copy;
        cin>>copy;
        if (copy==2){
            int n;
            cout<<"What struct u want to copy info from: ";
            cin>>n;
            obj[num].number=num;
            obj[num].amount=obj[n].amount;
            obj[num].value=obj[n].value;
            strcpy(obj[num].name,obj[n].name);
            strcpy(obj[num].date,obj[n].date);
            cout<<endl;
            return;
        }
    }
    obj[num].number=num;
    cin>>obj[num].name;
    cin>>obj[num].amount;
    cin>>obj[num].value;
    cin>>obj[num].date;
    cout<<endl;
}

void show(product* obj, int amount){
    cout<<left<<setw(4)<<"№"<<setw(10)<<"Name"<<setw(9)<<"Amount"<<setw(9)<<"Value"<<setw(5)<<"Date\n";
    for(int i=0;i<amount;i++){
//       удаленные элементы=-1
        cout<<left<<setw(2)<<obj[i].number<<setw(10)<<obj[i].name<<setw(9)<<obj[i].amount<<setw(9)<<obj[i].value<<obj[i].date<<endl;
    }
    cout<<endl;
}
void search(product* obj, int amount){
    cout<<"In which category to search?\n 0-if name\n 1-if amount\n 2-if value\n 3-if date\n";
    int cases;
    cin>>cases;
    if (cases==0){
        cout<<"What name to search?: ";
        char name[20];
        cin>>name;
        bool b=true;
        for(int i=0;i<amount;i++){
            
            if(!strcmp(obj[i].name, name)){
                if (b){
                    b=false;
                    cout<<left<<setw(4)<<"№"<<setw(10)<<"Name"<<setw(9)<<"Amount"<<setw(9)<<"Value"<<setw(5)<<"Date\n";
                }
                cout<<left<<setw(2)<<obj[i].number<<setw(10)<<obj[i].name<<setw(9)<<obj[i].amount<<setw(9)<<obj[i].value<<obj[i].date<<endl;
            }
        }
        if (b){
            cout<<"There's no such info\n";
        }
    }
    if(cases==1){
        cout<<"What amount to search?: ";
        int amount0;
        cin>>amount0;
        bool b=true;
        for(int i=0;i<amount;i++){
            if(obj[i].amount == amount0){
                if (b){
                    b=false;
                    cout<<left<<setw(4)<<"№"<<setw(10)<<"Name"<<setw(9)<<"Amount"<<setw(9)<<"Value"<<setw(5)<<"Date\n";
                }
                cout<<left<<setw(2)<<obj[i].number<<setw(10)<<obj[i].name<<setw(9)<<obj[i].amount<<setw(9)<<obj[i].value<<obj[i].date<<endl;
            }
        }
        if (b){
            cout<<"There's no such info\n";
        }
    }
    if(cases==2){
        cout<<"What value to search?: ";
        float value;
        cin>>value;
        bool b=true;
        for(int i=0;i<amount;i++){
            if(abs(value - obj[i].value) <0.0000001){
                if (b){
                    b=false;
                    cout<<left<<setw(4)<<"№"<<setw(10)<<"Name"<<setw(9)<<"Amount"<<setw(9)<<"Value"<<setw(5)<<"Date\n";
                }
                cout<<left<<setw(2)<<obj[i].number<<setw(10)<<obj[i].name<<setw(9)<<obj[i].amount<<setw(9)<<obj[i].value<<obj[i].date<<endl;
            }
        }
        if (b){
            cout<<"There's no such info\n";
        }
    }
    if (cases==3){
        cout<<"What date to search?: ";
        char date[20];
        cin>>date;
        bool b=true;
        for(int i=0;i<amount;i++){
            if(!strcmp(obj[i].date, date)){
                if (b){
                    b=false;
                    cout<<left<<setw(4)<<"№"<<setw(10)<<"Name"<<setw(9)<<"Amount"<<setw(9)<<"Value"<<setw(5)<<"Date\n";
                }
                cout<<left<<setw(2)<<obj[i].number<<setw(10)<<obj[i].name<<setw(9)<<obj[i].amount<<setw(9)<<obj[i].value<<obj[i].date<<endl;
            }
        }
        if (b){
            cout<<"There's no such info\n";
        }
    }
}
void change(product* obj, int amount){
    cout<<"In which category to change?\n 0-if name\n 1-if amount\n 2-if value\n 3-if date\n";
    int cases;
    cin>>cases;
    if (cases==0){
        cout<<"what name to delete/change\n";
        char name[20];
        cin>>name;
        cout<<" 0 -to delete\n 1 -to change\n";
        int x;
        cin>>x;
        bool b=true;
        for(int i=0;i<amount;i++){
            if(!strcmp(obj[i].name, name)){
                if (b)
                b=false;
                if(x==0)
                    strcpy(obj[i].name, "\0");
                if(x==1){
                    cout<<"Change to what: ";
                    char string[10];
                    cin>>string;
                    strcpy(obj[i].name, string);
                }
            }
        }
        if (b){
            cout<<"There's no such info\n";
        }
    }
    if (cases==3){
        cout<<"what date to delete/change\n";
        char date[20];
        cin>>date;
        cout<<" 0 -to delete\n 1 -to change\n";
        int x;
        cin>>x;
        bool b=true;
        for(int i=0;i<amount;i++){
            if(!strcmp(obj[i].date, date)){
                if (b)
                b=false;
                if(x==0)
                    strcpy(obj[i].date, "\0");
                if(x==1){
                    cout<<"Change to what: ";
                    char string[10];
                    cin>>string;
                    strcpy(obj[i].date, string);
                }
            }
        }
        if (b){
            cout<<"There's no such info\n";
        }
    }
    if (cases==1){
        cout<<"what amount to delete/change\n";
        int amount0;
        cin>>amount0;
        cout<<" 0 -to delete\n 1 -to change\n";
        int x;
        cin>>x;
        bool b=true;
        for(int i=0;i<amount;i++){
            if(obj[i].amount == amount0){
                if (b)
                    b=false;
                if(x==0)
                    obj[i].amount=-1;
                if(x==1){
                    cout<<"Change to what: ";
                    int am;
                    cin>>am;
                    obj[i].amount = am;
                }
            }
        }
        if (b){
            cout<<"There's no such info\n";
        }
    }
    if(cases==2){
        cout<<"What value to delete/change?\n";
        float value;
        cin>>value;
        cout<<" 0 -to delete\n 1 -to change\n";
        int x;
        cin>>x;
        bool b=true;
        for(int i=0;i<amount;i++){
            if(abs(value - obj[i].value) <0.0000001){
                if (b)
                    b=false;
                if(obj[i].value == value){
                if(x==0)
                    obj[i].value=-1;
                if(x==1){
                    cout<<"Change to what: ";
                    float am;
                    cin>>am;
                    obj[i].value = am;
                }
                }
            }
        }
        if (b){
            cout<<"There's no such info\n";
        }
    }
}

void sort(product* obj, int amount){
    for(int i=1;i<amount;i++){
        int j=i-1;
        product x=obj[i];
        while(x.value>obj[j].value){
            obj[j+1]=obj[j];
            j--;
            if(j<0) break;
        }
        obj[j+1]=x;
    }
    bool b=true;
    for(int i=0;abs(obj[i].value - 100.000)<0.00001 && i<amount;i++){
        if(b){
            b=false;
            cout<<left<<setw(4)<<"№"<<setw(10)<<"Name"<<setw(9)<<"Amount"<<setw(9)<<"Value"<<setw(5)<<"Date\n";
        }
        cout<<left<<setw(2)<<obj[i].number<<setw(10)<<obj[i].name<<setw(9)<<obj[i].amount<<setw(9)<<obj[i].value<<obj[i].date<<endl;
    }
    for(int i=0;i<amount;i++)
        obj[i].number=i;
}
void changestruct(product* obj, int amount){
    cout<<"Enter:\n 0-if delete\n 1-if change\n";
    int x;
    cin>>x;
    if (x==0){
        int y;
        cout<<"What struct to delete?: ";
        cin>>y;
        for(int i=0;i<amount;i++){
            if(i==y){
                for(int j=i;j<amount-1;j++)
                    obj[j]=obj[j+1];
                break;
            }
        }
    }
    else
        if (x==1){
            cout<<"What struct to change?: ";
            int y;
            cin>>y;
            fillstruct(obj,y);
    }
}
