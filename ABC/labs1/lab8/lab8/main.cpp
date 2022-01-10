#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

void Solve(double a, double b, double h, double eps);

int main(int argc, const char * argv[]) {
    long double a, b, h, eps;
    cout << "Введите числа a, b, h, eps:" << '\n';
    cout << "a = ";
    cin >> a;
    cout << "b = ";
    cin >> b;
    cout << "h = ";
    cin >> h;
    cout << "eps = ";
    cin >> eps;
    Solve(a, b, h, eps);
    return 0;
}


void Solve(double a, double b, double h, double eps)
{
    cout << " *********************************************************** " << '\n';
    cout << " *     x      |    S(x)    |    Y(x)    |   |S - Y|  |  n  * " << '\n';
    cout << " *********************************************************** " << '\n';
    for (double x = a; x < b + h / 2; x += h)
    {
        double Y, S = 0, f, p, intp, fracp, trash;
        __asm
        {
            //p = cos(x) * log2(e)
            FLD x
            FCOS
            FLDL2E
            FMUL
            FSTP p
            
            //intp = 2 ^ int(p)
            FLD p
            FLD1
            FSCALE
            FSTP intp
            FSTP trash

            //fracp = 2 ^ frac(p)
            FLD1
            FLD p
            FPREM
            F2XM1
            FADD
            FSTP fracp

            //Y = pow(exp(1.0L), cos(x)) * cos(sin(x));
            FLD intp
            FLD fracp
            FMUL

            FLD x
            FSIN
            FCOS
            FMUL
            FSTP Y

            //S = 1.0L, f = 1.0L;
            FLD1
            FSTP S

            FLD1
            FSTP f
        }
        int k = 1;
        while (abs(S - Y) > eps) {
            __asm
            {
                //f *= k;
                FLD f
                FILD k
                FMUL
                FSTP f

                //S += cos(n * x) / f;
                FLD S
                FILD k
                FLD x
                FMUL
                FCOS
                FLD f
                FDIV
                FADD
                FSTP S
            }
            ++k;
        }
        cout << setprecision(3) << scientific << showpos
        << " * " << x << " | " << S << " | " << Y << " | " << abs(S - Y) << " | "
        << noshowpos << right << setw(2) << k << "  * " << '\n';
    }
    cout << " *********************************************************** " << '\n';
}
