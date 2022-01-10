using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FileManager
{
    class ETLOptions : Options
    {
        public MovingOptions MovingOptions { get; set; } = new MovingOptions();
        public WatcherOptions WatcherOptions { get; set; } = new WatcherOptions();
        public ArchiveOptions ArchiveOptions { get; set; } = new ArchiveOptions();
        public Logger.LoggingOptions LoggingOptions { get; set; } = new Logger.LoggingOptions();

        [Converter.JsonIgnore]
        [Converter.XMLIgnore]
        public string Report { get; protected set; } = "";
        public ETLOptions() { }

        public ETLOptions(WatcherOptions watcherOptions, MovingOptions movingOptions, ArchiveOptions archiveOptions)
        {
            WatcherOptions = watcherOptions;
            MovingOptions = movingOptions;
            ArchiveOptions = archiveOptions;
        }
    }
}
