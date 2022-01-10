#include <iostream>
#include <string>

std::string solve(long double a, long double b, long double c);

int main(int argc, const char * argv[]) {
    long double a, b, c;
    std::cout << "Введите коэффициенты уравнения ax^2 + bx + c:" << '\n';
    std::cout << "a = ";
    std::cin >> a;
    std::cout << "b = ";
    std::cin >> b;
    std::cout << "c = ";
    std::cin >> c;
    std::cout << solve(a, b, c) << '\n';
    return 0;
}

std::string solve(long double a, long double b, long double c)
{
    const long double LD_4 = 4.0L;
    if (a == 0) return "Уравнение не является квадратным (т.к. a = 0)";

    long double D;
    __asm
    {
        FLD b
        FLD b
        FMUL
        FLD LD_4
        FLD a
        FLD c
        FMUL
        FMUL
        FSUB
        FSTP D
    }
    if (!isfinite(D)) return "Дискриминант не является конечным числом";
    
    if (D < 0.0L) return "Нет вещественных корней";
    
    if (D == 0.0L) {
        long double x;
        __asm
        {
            FLD b
            FCHS
            FLD a
            FLD a
            FADD
            FDIV
            FSTP x
        }
        return "x = " + std::to_string(x);
    }
    if (D > 0.0L) {
        long double x1, x2;
        __asm
        {
            FLD b
            FCHS
            FLD D
            FSQRT

            FSUB

            FLD a
            FLD a
            FADD
            FDIV

            FSTP x1
        }
        __asm
        {
            FLD b
            FCHS
            FLD D
            FSQRT

            FADD

            FLD a
            FLD a
            FADD
            FDIV

            FSTP x2
        }
        return "x1 = " + std::to_string(x1) + ", " + "x2 = " + std::to_string(x2);
    }
    return "Возникла неизвестная ошибка";
}
