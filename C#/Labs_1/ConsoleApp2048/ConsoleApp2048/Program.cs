using System;
using System.Diagnostics;
namespace ConsoleApp2048
{
    class Program
    {
        int MenuInput()
        {
            string buffer = Console.ReadLine();
            if ((buffer[0] - '0' >= 0 && buffer[0] - '0' <= 2) && buffer.Length == 1)
            { 
                   return Convert.ToInt32(buffer);
            }
            else
            {
                return -1;
            }
        }

        bool Menu() 
        {
            Console.WriteLine("* * * * * * * * * * * * * * * *");
            Console.WriteLine("* Menu:                       *");
            Console.WriteLine("* Enter 0 to exit:            *");
            Console.WriteLine("* Enter 1 to start a game:    *");
            Console.WriteLine("* Enter 2 to read the rules:  *");
            Console.WriteLine("* * * * * * * * * * * * * * * *");
            Console.Write("* Your input: ");
            switch (MenuInput())
            {
                case 0:
                    return false;
                case 1:
                    Start();
                    return false;
                case 2:
                    Console.Clear();
                    Console.WriteLine("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n" +
                                      "* 2048 is played on 4×4 grid, with numbered tiles that slide when a player moves them using the four arrow keys.  *\n" +
                                      "* Every turn, a new tile will randomly appear in an empty spot on the board with a value of either 2 or 4.        *\n" +
                                      "* Tiles slide as far as possible in the chosen direction until they are stopped by another tile or the grid edge. *\n" +
                                      "* If two tiles of the same number collide while moving, they will merge into a tile with the total value.         *\n" +
                                      "* The resulting tile cannot merge with another tile again in the same move.                                       *\n" +
                                      "* You need to reach 2048 :) Good luck!                                                                            *\n" +
                                      "* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *");
                    return true;
                default:
                    Console.Clear();
                    Console.WriteLine(">>>Invalid input...Retry");
                    return true;
            }
        }
       void Start()
        {
            Model model = new Model(4);
            model.Start();
            while (true)
            {
                Show(model);
                switch(Console.ReadKey(false).Key)
                {
                    case ConsoleKey.LeftArrow: 
                        model.Left();
                        break;
                    case ConsoleKey.RightArrow: 
                        model.Right();
                        break;
                    case ConsoleKey.DownArrow: 
                        model.Down();
                        break;
                    case ConsoleKey.UpArrow: 
                        model.Up();
                        break;
                    case ConsoleKey.Escape:
                        return;
                }
            }
        }

        void Show(Model model)
        {
            Console.Clear();
            ConsoleColor[] colors = (ConsoleColor[]) ConsoleColor.GetValues(typeof(ConsoleColor));
            for (int i = 0; i < model.Size; i++)
            {
                for (int j = 0; j < model.Size; j++)
                {
                    int number = model.GetMap(i, j);
                    Console.SetCursorPosition(j * 5, i * 2);
                    if (number != 0)
                    {
                        if (number <= 2048)
                        {
                            Console.ForegroundColor = colors[(int)Math.Log2(number)];
                        }
                        else
                        {
                            Console.ForegroundColor = ConsoleColor.Magenta;
                        }
                        Console.Write(number.ToString());
                        Console.ResetColor();
                    }
                    else
                    {
                        Console.Write("*");
                    }  
                }
            }
            if (model.IsGameOver())
            {
                Console.ForegroundColor = ConsoleColor.Red;
                Console.Write("\nGame over :(");
                Console.ResetColor();
            } else if (model.IsGameWin())
            {
                Console.ForegroundColor = ConsoleColor.Yellow;
                Console.Write("\nYou win! :)");
                Console.ResetColor();
            }
            Console.WriteLine("\nPress escape to end a program");
        }
        static void Main(string[] args)
        {
            Program program = new Program();
            while(program.Menu());
        }
        
    }
}