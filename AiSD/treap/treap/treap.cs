
using System;

namespace treap
{
    public class Treap
    {
        public int Key;
        public int Priority;

        public Treap Left;
        public Treap Right;
        public Treap Parent;
        public Treap(int key, int priority, Treap left = null, Treap right = null, Treap parent = null)
        {
            this.Key = key;
            this.Priority = priority;
            this.Left = left;
            if (left != null) left.Parent = this;
            this.Right = right;
            if (right != null) right.Parent = this;
            if (parent != null) this.Parent = parent;
        }
    
        public static Treap Merge(Treap L, Treap R)
        {
            if (L == null) return R;
            if (R == null) return L;

            if (L.Priority > R.Priority)
            {
                var newR = Merge(L.Right, R);
                return new Treap(L.Key, L.Priority, L.Left, newR);
            }
            else
            {
                var newL = Merge(L, R.Left);
                return new Treap(R.Key, R.Priority, newL, R.Right);
            }
        }
        
        public void Split(int x, out Treap L, out Treap R)
        {
            Treap newTree = null;
            if (this.Key <= x)
            {
                if (Right == null)
                    R = null;
                else
                    Right.Split(x, out newTree, out R);
                L = new Treap(this.Key, Priority, Left, newTree);
            }
            else
            {
                if (Left == null)
                    L = null;
                else
                    Left.Split(x, out L, out newTree);
                R = new Treap(this.Key, Priority, newTree, Right);
            }
        }
        
        public static Treap Build(int[] keys)
        {
            Array.Sort(keys);
            var tree = new Treap(keys[0], (new Random()).Next());
            var last = tree;

            for (int i = 1; i < keys.Length; ++i)
            {
                var priority = (new Random()).Next();
                if (last.Priority > priority)
                {
                    last.Right = new Treap(keys[i], priority, parent: last);
                    last = last.Right;
                }
                else
                {
                    Treap cur = last;
                    while (cur.Parent != null && cur.Priority <= priority)
                        cur = cur.Parent;
                    if (cur.Priority <= priority)
                        last = new Treap(keys[i], priority, cur);
                    else
                    {
                        last = new Treap(keys[i], priority, cur.Right, null, cur);
                        cur.Right = last;
                    }
                }
            }

            while (last.Parent != null)
            {
                last = last.Parent;
            }

            return last;
        }
        
        public Treap Insert(int x)
        {
            Treap l, r;
            Split(x, out l, out r);
            Treap m = new Treap(x, new Random().Next());
            return Merge(Merge(l, m), r);
        }
        
        public Treap Erase(int x)
        {
            Treap l, m, r;
            Split(x - 1, out l, out r);
            r.Split(x, out m, out r);
            return Merge(l, r);
        }

        public static int getHeight(Treap tree)
        {
            if (tree == null) return 0;

            return Math.Max(getHeight(tree.Left), getHeight((tree.Right))) + 1;
        }

        public Treap Search(int value)
        {
            var current = this;
            while (current != null && current.Key != value)
            {
                if (current.Key < value)
                {
                    current = current.Right;
                }
                else
                {
                    current = current.Left;
                }
            }
            
            return current;
        }

        public Treap begin()
        {
            var curr = this;
            while (curr.Left != null)
            {
                curr = curr.Left;
            }

            return curr;
        }
        
        public Treap end()
        {
            var curr = this;
            while (curr.Right != null)
            {
                curr = curr.Right;
            }

            return curr;
        }

        public Treap next()
        {
            if (this.Right != null)
            {
                var curr = this.Right;
                while (curr.Left  != null)
                {
                    curr = curr.Left;
                }

                return curr;
            }

            var node = this;
            var parentNode = this.Parent;
            while (parentNode != null && node == parentNode.Right)
            {
                node = parentNode;
                parentNode = parentNode.Parent;
            }
            return parentNode;
        }
        
        public Treap prev()
        {
            if (this.Left != null)
            {
                var curr = this.Left;
                while (curr.Right  != null)
                {
                    curr = curr.Right;
                }

                return curr;
            }

            var node = this;
            var parentNode = this.Parent;
            while (parentNode != null && node == parentNode.Left)
            {
                node = parentNode;
                parentNode = parentNode.Parent;
            }
            return parentNode;
        }
    }
}