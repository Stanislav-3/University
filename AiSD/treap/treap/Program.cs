using System;
using System.Collections.Generic;

namespace treap
{
    class Program
    {
        static void Main(string[] args)
        {
            const int n = 1000000;
            int[] keys = new int[n];

            for (int i = 0; i < n; i++)
            {
                keys[i] = (new Random()).Next();
                // keys[i] = i;
            }
            
            
            System.Diagnostics.Stopwatch myStopwatch = new System.Diagnostics.Stopwatch();
            myStopwatch.Start();
            
            Treap treap = Treap.Build(keys);

            myStopwatch.Stop();
            Console.WriteLine("*** Time ***\n" +
                              $"Sec: {myStopwatch.Elapsed.Seconds}, ms: {myStopwatch.Elapsed.Milliseconds}\n" +
                              "************\n");
            
            Console.Write("*** Height ***\n" +
                          $"Actual height: {Treap.getHeight(treap)}\n" +
                          $"Log2({n}) = {Math.Log2(n)}\n" +
                          "**************");
            
            Console.WriteLine();Console.WriteLine();
            
            // var node = treap.begin();
            // for (int i = 0; i < n; ++i)
            // {
            //     Console.WriteLine(node.Key);
            //     node = node.next();
            // }
        }
    }
}