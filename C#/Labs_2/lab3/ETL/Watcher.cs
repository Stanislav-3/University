using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ETL
{
    class Watcher
    {
        FileSystemWatcher fileSystemWatcher;
        Logger logger;
        string sourceDir;
        string targetDir;
        bool enableLogging, enableArchiveDirectory;
        CompressionLevel compressionLevel;
        string report;

        public Watcher(MovingOptions movingOptions, WatcherOptions watcherOptions, ArchiveOptions archiveOptions, string report)
        {
            this.sourceDir = movingOptions.SourceDirectory;
            this.targetDir = movingOptions.TargetDirectory;

            Directory.CreateDirectory(sourceDir);
            Directory.CreateDirectory(targetDir);

            fileSystemWatcher = new FileSystemWatcher(sourceDir);
            fileSystemWatcher.Filter = watcherOptions.Filter;
            fileSystemWatcher.Created += OnCreated;

            enableLogging = movingOptions.EnableLogging;
            enableArchiveDirectory = movingOptions.EnableArchiveDirectory;
            compressionLevel = archiveOptions.CompressionLevel;
            this.report = report;
            logger = new Logger(targetDir);
        }

        private void OnCreated(object sender, FileSystemEventArgs e) 
        {
            string path = e.FullPath;
            try
            {
                FileInfo fileInfo = new FileInfo(path);
                DateTime dateTime = fileInfo.LastWriteTime;
                string year = dateTime.ToString("yyyy");
                string month = dateTime.ToString("MM");
                string day = dateTime.ToString("dd");

                byte[] key, iv;
                (key, iv) = Encryptor.CreateKeyAndIV();

                string name = Path.GetFileNameWithoutExtension(path);
                string extension = Path.GetExtension(path);
                string fileName = Path.GetFileName(path);
                string gzPath = Path.Combine(targetDir, name + ".gz");
                string newPath = Path.Combine(targetDir, name + extension);

                //encrypting
                byte [] content = File.ReadAllBytes(path);
                content = Encryptor.Encrypt(content, key, iv);
                File.WriteAllBytes(path, content);


                //compressing and copying to targetDir
                Archive.Compress(path, gzPath);
                if (File.Exists(path)) File.Delete(path);

                if (enableArchiveDirectory)
                {
                    //copying to additional archive
                    char sep = Path.DirectorySeparatorChar;
                    string archiveDir = Path.Combine(targetDir, $"archive{sep}year {year}{sep}month {month}{sep}day {day}");
                    string archiveName = name + '_' + dateTime.ToString("yyyy_MM_dd_HH_mm_ss") + ".gz";
                    string archivePath = Path.Combine(archiveDir, archiveName);
                    Directory.CreateDirectory(archiveDir);
                    File.Copy(gzPath, archivePath);
                }

                //decompressing
                Archive.Decompress(gzPath, newPath);
                if (File.Exists(gzPath)) File.Delete(gzPath);

                //decrypting
                content = File.ReadAllBytes(newPath);
                string decrypted = Encryptor.Decrypt(content, key, iv);
                File.WriteAllText(newPath, decrypted);

                report += $"File \"{name}\" is moved from \"{sourceDir}\" to \"{targetDir}\" successfully!";
                logger.Log(report);
            }
            catch(Exception exception) 
            {
                report += $"A following problem occured: {exception}";
                logger.Log(report);
            }
        }

        public void Start()
        {
            fileSystemWatcher.EnableRaisingEvents = true;
        }

        public void Stop()
        {
            fileSystemWatcher.EnableRaisingEvents = false;
        }
    }
}
