using System;
using System.Runtime.InteropServices;

namespace Task2
{
    class Functions
    {
        [DllImport("MyLib.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int Multiplication(int a, int b, int mod);
        [DllImport("MyLib.dll", CallingConvention = CallingConvention.StdCall)]
        public static extern int BinPow(int a, int n, int mod);
    }
    
    class Program
    {
        static void Main(string[] args)
        {
            int a, b, mod;
            Console.WriteLine("Input a:");
            while (!Int32.TryParse(Console.ReadLine(), out a))
            {
                Console.WriteLine("Invalid input...Retry");
            }
            Console.WriteLine("Input b:");
            while (!Int32.TryParse(Console.ReadLine(), out b))
            {
                Console.WriteLine("Invalid input...Retry");
            }
            Console.WriteLine("Input modulus:");
            while (!Int32.TryParse(Console.ReadLine(), out mod) || mod == 0)
            {
                Console.WriteLine("Invalid input...Retry");
            }
            Console.WriteLine($"({a} * {b}) mod {mod} = {Functions.Multiplication(a, b, mod)}");
            Console.WriteLine($"({a} ^ {b}) mod {mod} = {Functions.BinPow(a, b, mod)}");
        }
    }
}