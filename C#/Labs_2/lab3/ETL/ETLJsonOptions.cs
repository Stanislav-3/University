using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ETL
{
    class ETLJsonOptions : ETLOptions
    {
        public ETLJsonOptions(string json) : base()
        {
            ETLOptions options = Converter.Converter.DeserializeJson<ETLOptions>(json);
            ArchiveOptions = options.ArchiveOptions;
            MovingOptions = options.MovingOptions;
            WatcherOptions = options.WatcherOptions;
            Report = Validator.Validate(this);
        }
    }
}
