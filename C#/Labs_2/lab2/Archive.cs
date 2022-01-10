using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ETL
{
    class Archive
    {
        public static void Compress(string source, string target)
        {
            using (FileStream sourceStream = new FileStream(source, FileMode.Open))
            using (FileStream targetStream = File.Create(target))
            using (GZipStream gZipStream = new GZipStream(targetStream, CompressionMode.Compress))
            sourceStream.CopyTo(gZipStream);
        }

        public static void Decompress(string source, string target)
        {
            using (FileStream sourceStream = new FileStream(source, FileMode.OpenOrCreate))
            using (FileStream targetStream = File.Create(target))
            using (GZipStream gZipStream = new GZipStream(sourceStream, CompressionMode.Decompress))
            gZipStream.CopyTo(targetStream);
        }
    }
}
