using System;
using System.Diagnostics;
using System.IO;
using System.IO.Compression;
using System.IO.Enumeration;

namespace lab1
{
    public class FileManager
    {
        public FileManager()
        {
            CurrentPath = "/Users/stanislav/Desktop/c#/lab1";
        }

        public string CurrentPath
        {
            get { return _currentPath; }
            set
            {
                if (value == "" || !Directory.Exists(value))
                {
                    throw new Exception($"The directory \"{value}\" doesn't exist!");
                }
                else
                {
                    _currentPath = value;
                }
            }
        }

        private string _currentPath;

        public bool changeDirectory(string newPath)
        {
            try
            {
                CurrentPath = newPath;
            }
            catch (Exception exception)
            {
                Console.WriteLine(exception.Message);
                return false;
            }

            return true;
        }

        public bool CreateFile(string name)
        {
            if (!IsTxt(name))
            {
                name += ".txt";
            }
            
            string fileName = Path.Combine(CurrentPath, name);
            if (string.IsNullOrEmpty(fileName) || fileName.IndexOfAny(Path.GetInvalidFileNameChars()) > 0 || File.Exists(fileName))
            {
                return false;
            }

            try
            {
                File.CreateText(fileName);
            }
            catch
            {
                return false;
            }

            return true;
        }

        public bool RenameFile(string oldName, string newName)
        {
            string oldFileName = Path.Combine(CurrentPath, oldName);
            string newFileName = Path.Combine(CurrentPath, newName);
            if (!File.Exists(oldFileName) || File.Exists(newFileName))
            {
                return false;
            }

            try
            {
                File.Move(oldFileName, newFileName);
            }
            catch
            {
                return false;
            }
            return true;
        }

        public bool ReadFile(string name)
        {
            string fileName = Path.Combine(CurrentPath, name);
            string content;
            try
            {
                content = File.ReadAllText(fileName);
            }
            catch
            {
                return false;
            }

            if (string.IsNullOrEmpty(content))
            {
                Console.WriteLine("* Nothing *");
            }
            else
            {
                Console.WriteLine(content);
            }

            return true;
        }

        public bool WriteFile(string name)
        {
            string fileName = Path.Combine(CurrentPath, name);
            if (!File.Exists(fileName) || new FileInfo(fileName).IsReadOnly)
            {
                return false;
            }
            
            Console.WriteLine("Enter the text:");
            string content = Console.ReadLine();
            try
            {
                File.AppendAllText(fileName, content);
            }
            catch
            {
                return false;
            }

            return true;
        }

        public bool MoveFile(string name, string newDirectory)
        {
            string oldFileName = Path.Combine(CurrentPath, name);
            string newFileName = Path.Combine(newDirectory, name);
            if (!File.Exists(oldFileName) || !Directory.Exists(newDirectory) || File.Exists(newFileName))
            {
                return false;
            }

            try
            {
                File.Move(oldFileName, newFileName);
            }
            catch
            {
                return false;
            }

            return true;
        }
        
        public bool CopyFile(string name, string newDirectory)
        {
            string oldFileName = Path.Combine(CurrentPath, name);
            string newFileName = Path.Combine(newDirectory, name);
            if (!File.Exists(oldFileName) || !Directory.Exists(newDirectory) || File.Exists(newFileName))
            {
                return false;
            }

            try
            {
                File.Copy(oldFileName, newFileName);
            }
            catch
            {
                return false;
            }

            return true;
        }

        public bool CompressFile(string fName)
        {
            string aName = fName.Remove(fName.Length - 3) + "gz";
            try
            {
                using var originalFileStream = new FileStream(Path.Combine(CurrentPath, fName), FileMode.Open);
                using var compressedFileStream = new FileStream(Path.Combine(CurrentPath, aName), FileMode.OpenOrCreate);
                using var compressionStream = new GZipStream(compressedFileStream, CompressionMode.Compress);
                originalFileStream.CopyTo(compressionStream);
                File.Delete(Path.Combine(CurrentPath, fName));
            }
            catch
            {
                return false;
            }

            return true;
        }

        public bool DecompressFile(string aName)
        {
            if (!IsGz(aName))
            {
                return false;
            }

            try
            {
                string currentFileName = Path.Combine(CurrentPath, aName);
                using var originalFileStream = new FileStream(currentFileName, FileMode.Open);
                string newFileName = currentFileName.Remove(currentFileName.Length - 2) + "txt";
                
                using var decompressedFileStream = File.Create(newFileName);
                using var decompressionStream = new GZipStream(originalFileStream, CompressionMode.Decompress);
                decompressionStream.CopyTo(decompressedFileStream);
                File.Delete(currentFileName);
            }
            catch
            {
                return false;
            }

            return true;
        }
        public bool DeleteFile(string name)
        {
            string fileName = CurrentPath + Path.DirectorySeparatorChar + name;
            if (!File.Exists(fileName))
            {
                return false;
            }

            try
            {
                File.Delete(fileName);
            }
            catch
            {
                return false;
            }

            return true;
        }

        public bool FileInfo(string name)
        {
            string fileName = CurrentPath + Path.DirectorySeparatorChar + name;
            if (!File.Exists(fileName))
            {
                return false;
            }

            FileInfo fileInfo;
            try
            {
                fileInfo = new FileInfo(fileName);
            }
            catch
            {
                return false;
            }

            Console.WriteLine($"Full file name: {fileInfo.FullName}" +
                              $"File size: {fileInfo.Length}\n" +
                              $"Creation time: {fileInfo.CreationTime}\n" +
                              $"Last access time: {fileInfo.LastAccessTime}\n" +
                              $"Last write time: {fileInfo.LastWriteTime}\n" +
                              $"Readonly: {fileInfo.IsReadOnly}\n" +
                              $"{fileInfo.Attributes}");
            return true;
        }

        public void ViewTxtFiles()
        {
            string[] allFiles = Directory.GetFiles(CurrentPath);
            int counter = 0;
            Console.WriteLine($"Text files in \"{CurrentPath}\"");
            foreach (string fileName in allFiles)
            {
                if (Path.GetExtension(fileName) != ".txt") continue;
                Console.WriteLine(Path.GetFileName(fileName));
                counter++;
            }
            if (counter == 0)
            {
                Console.WriteLine("*Nothing*");
            }
        }
        
        public void ViewGzFiles()
        {
            string[] allFiles = Directory.GetFiles(CurrentPath);
            int counter = 0;
            Console.WriteLine($"Gz files in \"{CurrentPath}\"");
            foreach (string fileName in allFiles)
            {
                if (Path.GetExtension(fileName) != ".gz") continue;
                Console.WriteLine(Path.GetFileName(fileName));
                counter++;
            }
            if (counter == 0)
            {
                Console.WriteLine("*Nothing*");
            }
        }
        
        public void ViewAccessibleFiles()
        {
            string[] allFiles = Directory.GetFiles(CurrentPath);
            int counter = 0;
            Console.WriteLine($"Accessible files in \"{CurrentPath}\"");
            foreach (string fileName in allFiles)
            {
                if (Path.GetExtension(fileName) != ".txt") continue;
                Console.WriteLine(Path.GetFileName(fileName));
                counter++;
            }
            if (counter == 0)
            {
                Console.WriteLine("*Nothing*");
            }
        }
        private bool IsTxt(string name)
        {
            string fileName = Path.Combine(CurrentPath, name);
            try
            {
                if (Path.GetExtension(fileName) == ".txt")
                {
                    return true;
                }
            }
            catch
            {
                return false;
            }
            
            return false;
        }

        private bool IsGz(string name)
        {
            string fileName = Path.Combine(CurrentPath, name);
            try
            {
                if (Path.GetExtension(fileName) == ".gz")
                {
                    return true;
                }
            }
            catch
            {
                return false;
            }

            return false;
        }
    }
}