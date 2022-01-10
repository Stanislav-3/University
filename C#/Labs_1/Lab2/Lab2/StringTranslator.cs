using System;
using System.Collections.Generic;

/**
 * Дана строка, состоящая из строчных английских букв.
 * Заменить в ней все буквы, стоящие после гласных, на следующие по алфавиту (z заменяется на a).
 */
namespace Lab2
{
    public class StringTranslator
    {
        public StringTranslator()
        {
            Console.Write("Hello!\nEnter an english lowercase letters string\n");
            string str = Console.ReadLine();
            if (CheckInput(str) == false)
            {
                Console.WriteLine("Invalid input...");
                return;
            }
            Translate(str);
        }
        
        bool CheckInput(String str)
        {
            if (String.IsNullOrEmpty(str))
            {
                return false;
            }
            for (int i = 0, size = str.Length; i < size; i++)
            {
                if (!(str[i] >= 97 && str[i] <= 122) && str[i] != ' ')
                {
                    return false;
                }
            }
            return true;
        }
        
        void Translate(string str)
        {
            List<int> letterChangeIndexes = new List<int>();
            for (int i = 0, size = str.Length; i < size - 1; i++)
            {
                if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' || str[i] == 'o' || str[i] == 'u')
                {
                    letterChangeIndexes.Add(i + 1);
                }
            }
            int j = 0, letterChangeNumber = letterChangeIndexes.Count;
            for (int i = 0, size = str.Length; i < size; i++)
            {
                if (letterChangeNumber != 0 && i == letterChangeIndexes[j])
                {
                    if (str[i] == 'z')
                    {
                        Console.Write('a');
                    }
                    else
                    {
                        Console.Write((char)((int)str[i] + 1));
                    }
                    if (j < letterChangeNumber - 1)
                    {
                        j++;
                    }
                }
                else
                {
                    Console.Write(str[i]);
                }
            }
        }
    }
}