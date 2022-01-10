using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.ServiceProcess;
using System.Text;
using System.Threading.Tasks;

namespace ETL
{
    public partial class ETL : ServiceBase
    {
        Watcher watcher;
        ETLOptions options;
        MovingOptions movingOptions;
        ArchiveOptions archiveOptions;
        WatcherOptions watcherOptions;
        Logger logger;
        OptionsManager optionsManager = new OptionsManager(AppDomain.CurrentDomain.BaseDirectory);

        public ETL()
        {
            InitializeComponent();
        }

        void Config() 
        {
            options = optionsManager.GetOptions<ETLOptions>() as ETLOptions;
            movingOptions = optionsManager.GetOptions<MovingOptions>() as MovingOptions;
            archiveOptions = optionsManager.GetOptions<ArchiveOptions>() as ArchiveOptions;
            watcherOptions = optionsManager.GetOptions<WatcherOptions>() as WatcherOptions;
            logger = new Logger(movingOptions.TargetDirectory);
        }

        protected override void OnStart(string[] args)
        {
            Config();
            watcher = new Watcher(movingOptions, watcherOptions, archiveOptions, optionsManager.Report);
            watcher.Start();
            logger.Log("Service started...");
        }

        protected override void OnStop()
        {
            watcher.Stop();
            logger.Log("Service stopped...");
        }
    }
}
