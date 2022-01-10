using System;
using System.Collections.Generic;
using System.Text;

namespace DataAccessLayer.Settings
{
    public class SendingOptions
    {
        public string Target { get; set; } = @"C:\Users\Public\Desktop\TargetFolder";
        public int BatchSize { get; set; } = 100;
        public PullingModes PullingMode { get; set; } = PullingModes.FullTable;

        public enum PullingModes
        {
            ByBatches,
            FullTable,
            FullJoin
        }

        public SendingOptions()
        {

        }
    }
}
