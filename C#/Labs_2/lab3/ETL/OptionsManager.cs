using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ETL
{
    class OptionsManager
    {
        ETLOptions DefaultOptions;
        ETLJsonOptions Json;
        ETLXmlOptions Xml;
        bool jsonConfigured, xmlConfigured;
        public string Report { get; set; } = "";

        public OptionsManager(string path)
        {
            DefaultOptions = new ETLOptions();
            string options;
            //Пытаемся загрузить файл config.xml
            try
            {
                using (StreamReader sr = new StreamReader($@"{path}\config.xml"))
                {
                    options = sr.ReadToEnd();
                }
                Xml = new ETLXmlOptions(options);
                xmlConfigured = true;
                Report = Xml.Report;
                Report += "Xml options loaded successfully. ";
            }
            catch
            {
                xmlConfigured = false;
            }
            //Пытаемся загрузить файл appsettings.json
            try
            {
                using (StreamReader sr = new StreamReader($@"{path}\appsettings.json"))
                {
                    options = sr.ReadToEnd();
                }
                Json = new ETLJsonOptions(options);
                jsonConfigured = true;
                Report = Json.Report;
                Report += "Json options loaded successfully. ";
            }
            catch
            {
                jsonConfigured = false;
            }

            if (!jsonConfigured && !xmlConfigured)
            {
                Report += "Failed to load both of json and xml. Using default options, creating appsettings.json and config.xml";
                if (!File.Exists($@"{path}\appsettings.json"))
                {
                    string json = Converter.Converter.SerializeJson(DefaultOptions);
                    Validator.CreateDirectoryIfNotExist(path);
                    using (StreamWriter sw = new StreamWriter($@"{path}\appsettings.json"))
                    {
                        sw.Write(json);
                    }
                }
                if (!File.Exists($@"{path}\config.xml"))
                {
                    string xml = Converter.Converter.SerializeXML(DefaultOptions);
                    Validator.CreateDirectoryIfNotExist(path);
                    using (StreamWriter sw = new StreamWriter($@"{path}\config.xml"))
                    {
                        sw.Write(xml);
                    }
                }
            }
        }

        public Options GetOptions<T>()
        {
            if (jsonConfigured)
            {
                return SeekForOption<T>(Json);
            }
            else if (xmlConfigured)
            {
                return SeekForOption<T>(Xml);
            }
            else
            {
                return SeekForOption<T>(DefaultOptions);
            }
        }

        Options SeekForOption<T>(ETLOptions options)
        {
            if (typeof(T) == typeof(ETLOptions))
            {
                return options;
            }

            string name = typeof(T).Name;
            try
            {
                return options.GetType().GetProperty(name).GetValue(options, null) as Options;
            }
            catch
            {
                throw new NotImplementedException();
            }
        }
    }
}
