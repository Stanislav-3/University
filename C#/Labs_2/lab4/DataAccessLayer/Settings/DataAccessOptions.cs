using System;
using System.Collections.Generic;
using System.Text;

namespace DataAccessLayer.Settings
{
    public class DataAccessOptions
    {
        public ConnectingOptions ConnectionOptions { get; set; } = new ConnectingOptions();
        public SendingOptions SendingOptions { get; set; } = new SendingOptions();
        public DataAccessOptions()
        {

        }
    }
}
