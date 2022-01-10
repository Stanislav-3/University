using System;
using Converter;
using Logger;
using OptionsManager;
using ServiceLayer;
using DataAccessLayer;
using DataAccessLayer.System;
using DataAccessLayer.Models;
using DataAccessLayer.Settings;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace DataManager
{
    class Program
    {
        static void Main(string[] args)
        {
            IParser parser = new Converter.Converter();
            IValidator validator = new Validator();
            string directory = AppDomain.CurrentDomain.BaseDirectory;
            
            OptionsManager<DataAccessOptions> options =
                new OptionsManager<DataAccessOptions>(directory, parser, validator);

            LoggingOptions loggingOptions = new LoggingOptions();
            //loggingOptions.ConnectingOptions = options.GetOptions<ConnectingOptions>() as ConnectingOptions;
            loggingOptions.EnableLogging = true;
            ILogger logger = new Logger.Logger(loggingOptions, parser);
            ServiceLayer.ServiceLayer SL = new ServiceLayer.ServiceLayer(
                options.GetOptions<ConnectingOptions>() as ConnectingOptions,
                parser, logger);

            SendingOptions sendingOptions = options.GetOptions<SendingOptions>() as SendingOptions;

            logger.Log("Starting pulling data");
            if (sendingOptions.PullingMode == SendingOptions.PullingModes.FullTable)
            {
                int curIndex = 1;
                int maxID = SL.DAL.EmployeeMaxID();
                List<HumanResourcesInfo> info;
                while (curIndex < maxID)
                {
                    info = SL.GetPersonsRange(curIndex, sendingOptions.BatchSize);
                    int lastID = info.Last().Employee.BusinessEntityID;
                    string s = parser.SerializeXML(info);
                    using (StreamWriter sw = new StreamWriter($@"{sendingOptions.Target}\file{curIndex}-{lastID}.txt"))
                    {
                        sw.Write(s);
                    }
                    curIndex = lastID + 1;
                }
            }
            else if (sendingOptions.PullingMode == SendingOptions.PullingModes.ByBatches)
            {
                List<HumanResourcesInfo> info = SL.GetEmployees();
                SplitOnBatches(info, sendingOptions, parser);
            }
            else if (sendingOptions.PullingMode == SendingOptions.PullingModes.FullJoin)
            {
                List<HumanResourcesInfo> info = SL.GetHumanResourcesByJoin();
                SplitOnBatches(info, sendingOptions, parser);
            }

            logger.Log("Pulled all data successfully");
        }

        static void SplitOnBatches(List<HumanResourcesInfo> info, SendingOptions sendingOptions, IParser parser)
        {
            int curIndex = 0;
            while (curIndex < info.Count)
            {
                List<HumanResourcesInfo> subInfo = info.GetRange(curIndex,
                                                         Math.Min(sendingOptions.BatchSize, info.Count - curIndex));

                int firstID = subInfo.First().Employee.BusinessEntityID;
                int lastID = subInfo.Last().Employee.BusinessEntityID;
                string s = parser.SerializeXML(subInfo);
                using (StreamWriter sw = new StreamWriter($@"{sendingOptions.Target}\file{firstID}-{lastID}.txt"))
                {
                    sw.Write(s);
                }
                curIndex += sendingOptions.BatchSize;
            }
        }
    }
}