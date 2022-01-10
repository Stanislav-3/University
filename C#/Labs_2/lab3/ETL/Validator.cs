using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ETL
{
    class Validator
    {
        public static string Validate(ETLOptions options)
        {
            string report = "";
            #region Moving Validation
            MovingOptions moving = options.MovingOptions;
            if (!CreateDirectoryIfNotExist(moving.SourceDirectory))
            {
                report += "Cannot open source directory, using default. ";
                moving.SourceDirectory = @"C:\Users\Public\Desktop\SourceFolder";
                CreateDirectoryIfNotExist(moving.SourceDirectory);
            }
            if (!CreateDirectoryIfNotExist(moving.TargetDirectory))
            {
                report += "Cannot open target directory, using default. ";
                moving.TargetDirectory = @"C:\Users\Public\Desktop\TargetFolder";
                CreateDirectoryIfNotExist(moving.TargetDirectory);
            }
            #endregion
            #region Archive Validation
            ArchiveOptions archive = options.ArchiveOptions;
            if ((int)archive.CompressionLevel < 0 || (int)archive.CompressionLevel > 2)
            {
                report += "Compression level value can't be below 0 or above 2, using default value. ";
                archive.CompressionLevel = System.IO.Compression.CompressionLevel.Optimal;
            }
            #endregion
            #region Watcher Validation
            WatcherOptions watcher = options.WatcherOptions;
            if (watcher.Filter != "*.txt") 
            {
                report += "Filter can be only \"*.txt\", using default value. ";
                watcher.Filter = "*.txt";
            }
            #endregion
            return report;
        }

        public static bool CreateDirectoryIfNotExist(string path)
        {
            try
            {
                if (!Directory.Exists(path))
                {
                    Directory.CreateDirectory(path);
                }
                return true;
            }
            catch
            {
                return false;
            }

        }

        public static bool CreateFileIfNotExist(string path)
        {
            try
            {
                string name = path.Trim('\\').Split('\\').Last();
                string p = path.Substring(0, path.Length - name.Length);
                if (!Directory.Exists(p))
                {
                    Directory.CreateDirectory(p);
                }
                if (!File.Exists(path))
                {
                    File.Create(path).Close();
                }
                return true;
            }
            catch
            {
                return false;
            }
        }
    }
}
