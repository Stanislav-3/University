using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FileManager
{
    class MovingOptions : Options
    {
        public bool EnableArchiveDirectory { get; set; } = true;
        public bool EnableLogging { get; set; } = true;
        public string SourceDirectory { get; set; } = @"C:\Users\Public\Desktop\SourceFolder";
        public string TargetDirectory { get; set; } = @"C:\Users\Public\Desktop\TargetFolder";

        public MovingOptions() { }
    }
}
