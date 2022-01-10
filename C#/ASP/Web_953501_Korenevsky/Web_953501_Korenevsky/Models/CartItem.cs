using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Web_953501_Korenevsky.Entities;

namespace Web_953501_Korenevsky.Models
{
    public class CartItem
    {
        public Sweet Sweet { get; set; }
        public int Quantity { get; set; }
    }
}
