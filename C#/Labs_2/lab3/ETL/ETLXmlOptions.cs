using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ETL
{
    class ETLXmlOptions : ETLOptions
    {
        public ETLXmlOptions(string xml) : base()
        {
            ETLOptions options = Converter.Converter.DeserializeXML<ETLOptions>(xml);
            ArchiveOptions = options.ArchiveOptions;
            MovingOptions = options.MovingOptions;
            WatcherOptions = options.WatcherOptions;
            Report = Validator.Validate(this);
        }
    }
}
