using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Web_953501_Korenevsky.Entities
{
    public class SweetGroup
    {
        public int SweetGroupId { get; set; }
        public string GroupName { get; set; }
        public List<Sweet> Beers { get; set; }
    }
}
