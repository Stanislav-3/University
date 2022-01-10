#include <iostream>
#include <math.h>
const int n=1000;
float step(float a, float b){
    return (b-a)/n;
}
float lefttr(float step, float a){
    float sum=0;
    for (int i=0;i<n;i++)
         sum+=(pow(0.5*(a+i*step)+2, 0.5))/(pow(2*(a+i*step)*(a+i*step)+1, 0.5)+0.8);
    return sum*step;
}
float righttr(float step, float a){
    float sum=0;
    for (int i=1;i<=n;i++)
         sum+=(cos(0.8*(a+i*step)+1.2))/(1.5+sin((a+i*step)*(a+i*step)+0.6));
    return sum*step;
}
float centraltr(float step, float a){
    float sum=0;
    for (int i=0;i<n;i++)
        sum+=1/(pow((a+(i+0.5)*step)*(a+(i+0.5)*step)+3.2, 0.5));
    return sum*step;
}
float trapezium(float step,float a){
    float sum=((a+1)*sin(a)+(a+1+step*n)*sin(a+step*n))/2;
    for (int i=1;i<n;i++)
        sum+=((a+i*step)+1)*sin(a+i*step);
    return sum*step;
}
int main(int argc, const char * argv[]) {
    float a,b;
    a=0.4;
    b=1.2;
    std::cout<< lefttr(step(a, b), a)<<"\n";
    a=0.3;
    b=0.9;
    std::cout<< righttr(step(a, b), a)<<"\n";
    a=1.2;
    b=2.7;
    std::cout<< centraltr(step(a, b), a)<<"\n";
    a=1.6;
    b=2.4;
    std::cout<< trapezium(step(a, b), a)<<"\n";
    return 0;
}
