using System;

namespace Logger
{
    public class LoggingOptions
    {
        public DataAccessLayer.Settings.ConnectingOptions ConnectingOptions { get; set; } = new DataAccessLayer.Settings.ConnectingOptions();
        public bool EnableLogging { get; set; } = true;
        public LoggingOptions()
        {

        }
    }
}
