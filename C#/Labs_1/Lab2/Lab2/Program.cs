using System;

namespace Lab2
{
    class Program
    {
        static void Main(string[] args)
        {
            for (;;)
            {
                Console.WriteLine("Menu:\n" +
                                  "0) Exit\n" +
                                  "1) Output months in a certain language\n" +
                                  "2) Change the letters after the vowels with the following letter in the alphabet " +
                                  "in an english lowercase letters string\n" +
                                  "3) Shuffle a string");
                switch (Console.ReadLine())
                {
                    case "0":
                        return;
                    case "1":
                        Console.Clear();
                        new Months();
                        break;
                    case "2":
                        Console.Clear();
                        new StringTranslator();
                        break;
                    case "3":
                        Console.Clear();
                        new StringShuffle();
                        break;
                    default:
                        Console.Clear();
                        Console.WriteLine("Invalid input...Retry");
                        break;
                }
                Console.WriteLine();
            }
        }
    }
}