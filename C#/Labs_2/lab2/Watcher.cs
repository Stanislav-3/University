using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.IO;
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

        public Watcher(string sourceDir, string targetDir)
        {
            this.sourceDir = sourceDir;
            this.targetDir = targetDir;

            Directory.CreateDirectory(sourceDir);
            Directory.CreateDirectory(targetDir);

            logger = new Logger(targetDir);

            fileSystemWatcher = new FileSystemWatcher(sourceDir);
            fileSystemWatcher.Filter = "*.txt";
            fileSystemWatcher.Created += OnCreated;
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

                //encryting
                byte[] content = File.ReadAllBytes(path);
                content = Encryptor.Encrypt(content, key, iv);
                File.WriteAllBytes(path, content);

                //compressing and copying to targetDir
                Archive.Compress(path, gzPath);
                logger.Log($"File \"{name}\" is moved from \"{sourceDir}\" to \"{targetDir}\" successfully!");
                File.Delete(path);

                //copying to additional archive
                char sep = Path.DirectorySeparatorChar;
                string archiveDir = Path.Combine(targetDir, $"archive{sep}year {year}{sep}month {month}{sep}day {day}");
                string archiveName = name + '_' + dateTime.ToString("yyyy_MM_dd_HH_mm_ss") + ".gz";
                string archivePath = Path.Combine(archiveDir, archiveName);
                Directory.CreateDirectory(archiveDir);
                File.Copy(gzPath, archivePath);

                //decompressing
                Archive.Decompress(gzPath, newPath);
                File.Delete(gzPath);

                //decrypting
                content = File.ReadAllBytes(newPath);
                string decrypted = Encryptor.Decrypt(content, key, iv);
                File.WriteAllText(newPath, decrypted);
            }
            catch 
            {
                logger.Log("A problem occured...");
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
