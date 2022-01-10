using System;
using System.Text;
using System.Threading;

namespace ConsoleApp2048
{
    public class Model
    {
        private Map map;
        private bool isGameOver;
        private bool isGameWin;
        private bool moved; 
        static Random random = new Random();
        public int Size
        {
            get { return map.Size; }
        }

        public Model(int size)
        {
            map = new Map(size);
        }

        public void Start()
        {
            for (int i = 0; i < Size; i++)
            {
                for (int j = 0; j < Size; j++)
                {
                    map.Set(i, j, 0);
                }
            }
            AddRandomNumber();
            AddRandomNumber();
        }

        private void AddRandomNumber()
        {
            if (isGameOver) return;
            while (true)
            {
                int x = random.Next(0, map.Size);
                int y = random.Next(0, map.Size);
                if (map.Get(x, y) == 0)
                {
                    map.Set(x, y, random.Next(1, 3) * 2);
                    return;
                }
            }
        }
        
        private void Shift(int x, int y, int dx, int dy)
        {
            if (map.Get(x, y) > 0)
            {
                while (map.Get(x + dx, y + dy) == 0)
                {
                    map.Set(x + dx, y + dy, map.Get(x, y));
                    map.Set(x, y, 0);
                    x += dx;
                    y += dy;
                    moved = true;
                }
            }
        }

        private void Join(int x, int y, int dx, int dy)
        {
            if (map.Get(x, y) > 0)
            {
                if (map.Get(x, y) == map.Get(x + dx, y + dy))
                {
                    map.Set(x + dx, y + dy, map.Get(x, y) * 2);
                    while (map.Get(x - dx,y - dy) > 0)
                    {
                        map.Set(x, y, map.Get(x - dx, y - dy));
                        x -= dx;
                        y -= dy;
                    }
                    map.Set(x, y, 0);
                    moved = true;
                }
            }
        }

        // public void Movements(int dx, int dy)
        // {
        //     moved = false;
        //     for (int i = 0; i < map.Size; i++)
        //     {
        //         for (int j = 1; j < map.Size; j++)
        //         {
        //             Shift(i, j, dx, dy);
        //         }
        //         for (int j = 1; j < map.Size; j++)
        //         {
        //             Join(i, j, dx, dy);
        //         }
        //     }
        //     if (moved)
        //     {
        //         AddRandomNumber();
        //     }
        // }
        //
        // public void Left()
        // {
        //     Movements(0, -1);
        // }
        //
        // public void Right()
        // {
        //     Movements(0, -1);
        // }
        public void Left()
        {
            moved = false;
            for (int i = 0; i < map.Size; i++)
            {
                for (int j = 1; j < map.Size; j++)
                {
                    Shift(i, j, 0, -1);
                }
                for (int j = 1; j < map.Size; j++)
                {
                    Join(i, j, 0, -1);
                }
            }
            if (moved)
            {
                AddRandomNumber();
            }
        }
        
        public void Right()
        {
            moved = false;
            for (int i = 0; i < map.Size; i++)
            {
                for (int j = map.Size - 1; j >= 0; j--)
                {
                    Shift(i, j, 0, 1);
                }
                for (int j = map.Size - 1; j >= 0; j--)
                {
                    Join(i, j, 0, 1);
                }
            }
            if (moved)
            {
                AddRandomNumber();
            }
        }
        
        public void Down()
        {
            moved = false;
            for (int j = 0; j < map.Size; j++)
            {
                for (int i = map.Size - 2; i >= 0; i--)
                {
                    Shift(i, j, 1, 0);
                }
                for (int i = map.Size - 2; i >= 0; i--)
                {
                    Join(i, j, 1, 0);
                }
            }
            if (moved)
            {
                AddRandomNumber();
            }
        }
        
        public void Up()
        {
            moved = false;
            for (int j = 0; j < map.Size; j++)
            {
                for (int i = 1; i < map.Size; i++)
                { 
                    Shift(i, j, -1, 0 );
                }
                for (int i = 1; i < map.Size; i++)
                {
                    Join(i, j, -1, 0 );
                }
            }
            if (moved)
            {
                AddRandomNumber();
            }
        }

        public bool IsGameOver()
        {
            if (isGameOver)
            {
               return isGameOver; 
            }
            // isGameOver == false
            for (int i = 0; i < Size; i++)
            {
                for (int j = 0; j < Size; j++)
                {
                    if (map.Get(i, j) == 0)
                    {
                        return false;
                    }
                }
            }
            for (int i = 0; i < Size; i++)
            {
                for (int j = 0; j < Size; j++)
                {
                    if (map.Get(i, j) == map.Get(i, j + 1) ||
                        map.Get(i, j) == map.Get(i + 1, j))
                    {
                        return false;
                    };
                }
            }
            isGameOver = true;
            return isGameOver;
        }

        public bool IsGameWin()
        {
            if (isGameWin)
            {
                return isGameWin;
            }
            // isGameWin == false
            for (int i = 0; i < Size; i++)
            {
                for (int j = 0; j < Size; j++)
                {
                    if (GetMap(i, j) == 2048)
                    {
                        isGameWin = true;
                        return isGameWin;
                    }
                }
            }
            return false;
        }

        public int GetMap(in int x, in int y)
        {
            return map.Get(x, y);
        }
    }
}