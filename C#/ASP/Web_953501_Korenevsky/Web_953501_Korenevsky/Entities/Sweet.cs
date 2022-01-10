using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Web_953501_Korenevsky.Entities
{
    public class Sweet
    {
        public int SweetId { get; set; }
        public string SweetName { get; set; }
        public float SweetCalories { get; set; }
        public string Image { get; set; }

        public int SweetGroupId { get; set; }
        public SweetGroup Group { get; set; }
    }
}
