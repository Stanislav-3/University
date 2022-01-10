using System;
using Converter;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Logger
{
    public class Logger : ILogger
    {
        public LoggingOptions LoggingOptions { get; set; }
        DataAccessLayer.DataAccessLayer DAL;

        public void Log(string message)
        {
            if (LoggingOptions.EnableLogging)
            {
                DAL.Log(DateTime.Now, message);
            }
        }

        public Logger(LoggingOptions loggingOptions, IParser parser)
        {
            LoggingOptions = loggingOptions;
            DAL = new DataAccessLayer.DataAccessLayer(loggingOptions.ConnectingOptions, parser);
        }
    }
}
