using System;
using System.Collections.Generic;

namespace lab7
{
    class Program
    {
        static void Main(string[] args)
        {
            List<RationalNumber> numbers = new List<RationalNumber>()
            {
                new RationalNumber(7, 31),
                new RationalNumber(-2, 15),
                new RationalNumber(51),
                new RationalNumber(-7),
                (1, 3),
                (-57, 23),
                1,
                -4,
                1.1431341M,
                -5.21M,
                2.345,
                -1.789,
                RationalNumber.Parse("1/2", "s"),
                RationalNumber.Parse("8/20", "s"),
                RationalNumber.Parse("1.35(152)", "d"),
                RationalNumber.Parse("1.2", "d"),
                RationalNumber.Parse("1 2/3", "m"),
                RationalNumber.Parse("-7 5/7", "m")
            };
            while (true)
            {
                Console.Write("Menu:\n" +
                                  "1) Show all numbers\n" +
                                  "2) Show numbers in a definite format\n" +
                                  "3) Add a number\n" +
                                  "4) Delete a number\n" +
                                  "5) Delete all numbers\n" +
                                  "6) Sort numbers\n" +
                                  "7) Addition| Subtraction| Multiplication| Division\n" +
                                  "8) Comparison| Ceiling| Floor| Round| Min| Max\n" +
                                  "9) Exit\n>>>");
                int menuItem;
                while (!int.TryParse(Console.ReadLine(), out menuItem) || menuItem < 1 || menuItem > 9)
                {
                    Console.WriteLine("Error! Try again");
                }

                switch (menuItem)
                {
                    case 1:
                    {
                        Console.Clear();
                        Console.WriteLine("All numbers:");
                        if (NoNumbers(numbers)) break;
                        foreach (var number in numbers)
                        {
                            Console.WriteLine(number);
                        }

                        break;
                    }
                    case 2:
                    {
                        if (NoNumbers(numbers)) break;
                        Console.Write("Enter format:\n" +
                                      "\"s\" - b/c\n" +
                                      "\"m\" - a b/c\n" +
                                      "\"d\" - 1.123 or 1.2(3)\n" +
                                      "\"long\" - to long\n" +
                                      "\"decimal\" - to decimal\n>>>");
                        string format = Console.ReadLine();
                        if (format == "s" || format == "m" || format == "d")
                        {
                            Console.WriteLine("All numbers:");
                            foreach (var number in numbers)
                            {
                                Console.WriteLine(number.ToString(format));
                            }
                        }
                        else if (format == "long")
                        {
                            Console.WriteLine("All numbers:");
                            foreach (var number in numbers)
                            {
                                Console.WriteLine((long) number);
                            }
                        }
                        else if (format == "decimal")
                        {
                            Console.WriteLine("All numbers:");
                            foreach (var number in numbers)
                            {
                                Console.WriteLine((decimal) number);
                            }
                        }
                        else Console.WriteLine("Invalid input...");

                        break;
                    }
                    case 3:
                    {
                        Console.WriteLine("Enter number in any format:");
                        if (!RationalNumber.TryParse(Console.ReadLine(), out RationalNumber x))
                        {
                            Console.WriteLine("Invalid input...");
                        }
                        else
                        {
                            numbers.Add(x);
                            Console.WriteLine("New number successfully has been added!");
                        }

                        break;
                    }
                    case 4:
                    {
                        if (NoNumbers(numbers)) break;
                        Console.WriteLine("Enter number in any format:");
                        if (!RationalNumber.TryParse(Console.ReadLine(), out RationalNumber x))
                        {
                            Console.WriteLine("Invalid input...");
                        }
                        else if (numbers.Remove(x))
                        {
                            Console.WriteLine("New number successfully has been removed!");
                        }
                        else
                        {
                            Console.WriteLine("Error! Not found!");
                        }

                        break;
                    }
                    case 5:
                    {
                        if (NoNumbers(numbers)) break;
                        numbers.Clear();
                        Console.WriteLine("Done!");
                        break;
                    }
                    case 6:
                    {
                        if (NoNumbers(numbers)) break;
                        numbers.Sort();
                        Console.WriteLine("Done!");
                        break;
                    }
                    case 7:
                    {
                        Console.WriteLine("Enter the first rational number in any format");
                        if (!RationalNumber.TryParse(Console.ReadLine(), out RationalNumber a))
                        {
                            Console.WriteLine("Invalid input...");
                            continue;
                        }
                        Console.WriteLine("Enter the second rational number in any format");
                        if (!RationalNumber.TryParse(Console.ReadLine(), out RationalNumber b))
                        {
                            Console.WriteLine("Invalid input...");
                            continue;
                        }
                        Console.WriteLine();
                        if (b > 0)
                        {
                            Console.WriteLine(string.Concat(a, " + ", b, " = ", a + b));
                            Console.WriteLine(string.Concat(a, " - ", b, " = ", a - b));
                            Console.WriteLine(string.Concat(a, " * ", b, " = ", a * b));
                            Console.WriteLine(b == 0 
                                ? "Division by zero is not allowed!" 
                                : string.Concat(a, " / ", b, " = ", a / b));
                        }
                        else
                        {
                            Console.WriteLine(string.Concat(a, " + (", b, ") = ", a + b));
                            Console.WriteLine(string.Concat(a, " - (", b, ") = ", a - b));
                            Console.WriteLine(string.Concat(a, " * (", b, ") = ", a * b));
                            Console.WriteLine(b == 0 
                                ? "Division by zero is not allowed!"
                                : string.Concat(a, " / (", b, ") = ", a / b));
                        }
                        
                        break;
                    }

                    case 8:
                    {
                        Console.WriteLine("Enter the first rational number in any format");
                        if (!RationalNumber.TryParse(Console.ReadLine(), out RationalNumber a))
                        {
                            Console.WriteLine("Invalid input...");
                            continue;
                        }
                        Console.WriteLine("Enter the second rational number in any format");
                        if (!RationalNumber.TryParse(Console.ReadLine(), out RationalNumber b))
                        {
                            Console.WriteLine("Invalid input...");
                            continue;
                        }
                        Console.WriteLine();
                        if (a > b)
                        {
                            Console.WriteLine(string.Concat(a.ToString("d"), " > ", b.ToString("d")));
                        }
                        else if (a < b)
                        {
                            Console.WriteLine(string.Concat(a.ToString("d"), " < ", b.ToString("d")));
                        }
                        else
                        {
                            Console.WriteLine(string.Concat(a.ToString("d"), " = ", b.ToString("d")));
                        }
                        Console.WriteLine($"Ceiling: {RationalNumber.Ceiling(a)} | {RationalNumber.Ceiling(b)}");
                        Console.WriteLine($"Floor: {RationalNumber.Floor(a)} | {RationalNumber.Floor(b)}");
                        Console.WriteLine($"Round: {RationalNumber.Round(a)} | {RationalNumber.Round(b)}");
                        Console.WriteLine($"Min: {RationalNumber.Min(a, b).ToString("d")}");
                        Console.WriteLine($"Max: {RationalNumber.Max(a, b).ToString("d")}");
                        break;
                    }
                    case 9:
                        return;
                }
            }
        }

        static bool NoNumbers(List<RationalNumber> numbers)
        {
            if (numbers.Count == 0)
            {
                Console.WriteLine("No numbers...");
                return true;
            }

            return false;
        }
    }
}