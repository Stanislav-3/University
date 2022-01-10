using System;
using Logger;
using Converter;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ServiceProcess;
using OptionsManager;

namespace FileManager
{
    public partial class ETL : ServiceBase
    {
        Watcher watcher;

        ETLOptions options;

        ILogger dbLogger;
        IParser parser;
        Validator validator;

        OptionsManager.OptionsManager<ETLOptions> optionsManager;

        public ETL()
        {
            InitializeComponent();
        }

        void Config() 
        {
            parser = new Converter.Converter();
            validator = new Validator();
            optionsManager = new OptionsManager.OptionsManager<ETLOptions>(AppDomain.CurrentDomain.BaseDirectory, parser, validator);
        
            options = optionsManager.GetOptions<ETLOptions>() as ETLOptions;

            dbLogger = new Logger.Logger(optionsManager.GetOptions<Logger.LoggingOptions>() as Logger.LoggingOptions, parser);
        }

        protected override void OnStart(string[] args)
        {
            Config();
            watcher = new Watcher(options, dbLogger, optionsManager.Report);
            watcher.Start();
            dbLogger.Log("Service started...");
        }

        protected override void OnStop()
        {
            watcher.Stop();
            dbLogger.Log("Service stopped...");
        }
    }
}
