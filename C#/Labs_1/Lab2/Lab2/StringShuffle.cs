using System;
using System.Text;

/**
 * Реализовать эффективное перемешивание символов строки.
 */
namespace Lab2
{
    public class StringShuffle
    {
        public StringShuffle()
        {
            Console.WriteLine("Hello!\nInput a string you want to shuffle");
            string str = Console.ReadLine();
            if (String.IsNullOrEmpty(str))
            {
                Console.WriteLine("Invalid input...");
            }
            else
            {
                Console.WriteLine(Shuffle(str));
            }
        }
        string Shuffle(string str)
        {
            StringBuilder newStr = new StringBuilder(str);
            Random rand = new Random();
            for (int i = 0, size = str.Length; i < size; i++)
            {
                int j = rand.Next(size);
                (newStr[i], newStr[j]) = (newStr[j], newStr[i]);
            }
            return newStr.ToString();
        }
    }
}