using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ETL
{
    class Logger
    {
        string loggerPath;
        public Logger(string dir) 
        {
            Directory.CreateDirectory(dir);
            loggerPath = Path.Combine(dir, "log.txt");
            if (!File.Exists(loggerPath))
            {
                File.Create(loggerPath);
            }
        }

        public void Log(string info) 
        {
            string dateTime = DateTime.Now.ToString("dd.MM.yyyy hh:mm:ss");
            using (StreamWriter streamWriter = new StreamWriter(loggerPath, true))
            {
                streamWriter.WriteLine($"{dateTime} | {info}");
            }

        }
    }
}
