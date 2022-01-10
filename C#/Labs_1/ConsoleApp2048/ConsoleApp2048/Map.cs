using System.Reflection;

namespace ConsoleApp2048
{
    public class Map
    {
        public int Size { get; }

        private int[,] map;
        public Map(int size)
        {
            this.Size = size;
            map = new int[size, size];
        }

        public int Get(int x, int y)
        {
            if (OnMap(x, y))
            {
                return map[x, y];
            }
            return -1;
        }

        public void Set(int x, int y, int number)
        {
            if (OnMap(x, y))
            {
                map[x, y] = number;
            }
        }

        private bool OnMap(int x, int y)
        {
            return (x >= 0 && x < Size) &&
                   (y >= 0 && y < Size);
        }
    }
}