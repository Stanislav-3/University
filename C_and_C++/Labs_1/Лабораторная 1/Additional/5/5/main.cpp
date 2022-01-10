//5

#include <iostream>
#include <math.h>
#define pi 3.141592

using namespace std;

int main() {
    
    cout << "The length of circumference=";
    float l;
    cin >> l;
    
    cout << "Bounded circle area= " << (pow((l/2),2)/ pi) << endl;
    return 0;
}
