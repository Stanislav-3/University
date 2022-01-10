using System;
using System.Collections.Generic;
using System.Text;

namespace DataAccessLayer.Models
{
    public class JobCandidate
    {
        public int JobCandidateID { get; set; }
        public int BusinessEntityID { get; set; }
        public string Resume { get; set; }
        public DateTime ModifiedDate { get; set; }
    }
}
