using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Web_953501_Korenevsky.Entities;

namespace Web_953501_Korenevsky.Models
{
    public class Cart
    {
        public Dictionary<int, CartItem> Items { get; set; }
        public Cart()
        {
            Items = new Dictionary<int, CartItem>();
        }

        public int Count
        {
            get
            {
                return Items.Sum(item => item.Value.Quantity);
            }
        }

        virtual public void AddToCart(Sweet sweet)
        {
            // если объект есть в корзине
            // то увеличить количество
            if (Items.ContainsKey(sweet.SweetId))
            {
                Items[sweet.SweetId].Quantity++;
            }
            // иначе - добавить объект в корзину
            else
            {
                Items.Add(sweet.SweetId, new CartItem
                {
                    Sweet = sweet,
                    Quantity = 1
                });
            }
        }

        virtual public void RemoveFromCart(int id)
        {
            Items.Remove(id);
        }

        virtual public void ClearAll()
        {
            Items.Clear();
        }
    }
}
