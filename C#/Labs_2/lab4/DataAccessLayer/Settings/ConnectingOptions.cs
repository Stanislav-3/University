using System;
using System.Collections.Generic;
using System.Text;

namespace DataAccessLayer.Settings
{
    public class ConnectingOptions
    {
        public string DataSource { get; set; } = @"DESKTOP-TK1ILU0\SQLEXPRESS";
        public string Database { get; set; } = "AdventureWorks2017";
        public string User { get; set; } = @"DESKTOP-TK1ILU0\stas1";
        public string Password { get; set; } = "";
        public bool IntegratedSecurity { get; set; } = false;
        public ConnectingOptions()
        {

        }
    }
}
