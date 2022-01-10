using System;
using System.Collections.Generic;
using System.Text;

namespace DataAccessLayer.Models
{
    public class EmployeePayHistory
    {
        public int BussinessEntityID { get; set; }
        public DateTime RateChangeDate { get; set; }
        public decimal Rate { get; set; }
        public int PayFrequency { get; set; }
        public DateTime ModifiedDate { get; set; }
    }
}
