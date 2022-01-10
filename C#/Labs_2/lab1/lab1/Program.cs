using System;
using System.Diagnostics;

namespace lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            FileManager fileManager = new FileManager();
            for(;;)
            {
                Console.WriteLine("Menu:\n" +
                                  "0)  Exit\n" +
                                  "1)  Change current directory\n" +
                                  "2)  Create a file\n" +
                                  "3)  Rename a file\n" +
                                  "4)  Read a file\n" +
                                  "5)  Write to file\n" +
                                  "6)  Move a file\n" +
                                  "7)  Copy a file\n" +
                                  "8)  Archive a file\n" +
                                  "9)  Unarchive a file\n" +
                                  "10) File info\n" +
                                  "11) Delete a file\n" +
                                  $"Active directory: {fileManager.CurrentPath}");
                switch(Console.ReadLine()){
                    case "0":
                        return;
                    case "1":
                    {
                        Console.Clear();
                        Console.Write($"Old directory: {fileManager.CurrentPath}\n" +
                                      $"New directory: ");
                        if (fileManager.changeDirectory(Console.ReadLine()))
                        {
                            Console.WriteLine($"Directory is successfully changed!");
                        }

                        Console.WriteLine("Press any key to continue...");
                        Console.ReadKey();
                        Console.Clear();
                        break;
                    }
                    case "2":
                    {
                        Console.Clear();
                        fileManager.ViewAccessibleFiles();
                        Console.Write("Enter a file name: ");
                        string fileName = Console.ReadLine();
                        if (!fileManager.CreateFile(fileName))
                        {
                            if (fileName == "")
                            {
                                Console.WriteLine("Invalid name!");
                            }
                            else
                            {
                                Console.WriteLine(
                                    $"File \"{fileName}\" is already exists in \"{fileManager.CurrentPath}\"");
                            }
                        }
                        else
                        {
                            Console.WriteLine(
                                $"File \"{fileName}\" is successfully created in \"{fileManager.CurrentPath}\"");
                        }

                        Console.WriteLine("Press any key to continue...");
                        Console.ReadKey();
                        Console.Clear();
                        break;
                    }
                    case "3":
                    {
                        Console.Clear();
                        fileManager.ViewAccessibleFiles();
                        Console.Write("Old file name: ");
                        string oldName = Console.ReadLine();
                        Console.Write("New file name: ");
                        string newName = Console.ReadLine();
                        if (!fileManager.RenameFile(oldName, newName))
                        {
                            Console.Write("File is not renamed! ");
                        }
                        else
                        {
                            Console.WriteLine($"File is successfully renamed from \"{oldName}\" to \"{newName}\"");
                        }
                        
                        Console.WriteLine("Press any key to continue...");
                        Console.ReadKey();
                        Console.Clear();
                        break;
                    }
                    case "4":
                    {
                        Console.Clear();
                        fileManager.ViewAccessibleFiles();
                        Console.Write("File name: ");
                        string name = Console.ReadLine();
                        if (!fileManager.ReadFile(name))
                        {
                            Console.WriteLine($"The file {name} can't be read!");
                        }
                        
                        Console.WriteLine("Press any key to continue...");
                        Console.ReadKey();
                        Console.Clear();
                        break;
                    }
                    case "5":
                    {
                        Console.Clear();
                        fileManager.ViewAccessibleFiles();
                        Console.Write("File name: ");
                        string name = Console.ReadLine();
                        if (!fileManager.WriteFile(name))
                        {
                            Console.WriteLine($"The file \"{name}\" can't be written to!");
                        }
                        else
                        {
                            Console.WriteLine("The text is successfully written to file \"{name}\"");
                        }

                        Console.WriteLine("Press any key to continue...");
                        Console.ReadKey();
                        Console.Clear();
                        break;
                    }
                    case "6":
                    {
                        Console.Clear();
                        fileManager.ViewAccessibleFiles();
                        Console.Write("File name: ");
                        string name = Console.ReadLine();
                        Console.Write("New directory: ");
                        string newDirectory = Console.ReadLine();
                        if (!fileManager.MoveFile(name, newDirectory))
                        {
                            Console.Write("File is not moved! ");
                        }
                        else
                        {
                            Console.WriteLine($"File \"{name}\" is successfully moved from \"{fileManager.CurrentPath}\" to \"{newDirectory}\"");
                        }
                        
                        Console.WriteLine("Press any key to continue...");
                        Console.ReadKey();
                        Console.Clear();
                        break;
                    }
                    case "7":
                    {
                        Console.Clear();
                        fileManager.ViewTxtFiles();
                        Console.Write("File name: ");
                        string name = Console.ReadLine();
                        Console.Write("New directory: ");
                        string newDirectory = Console.ReadLine();
                        if (!fileManager.CopyFile(name, newDirectory))
                        {
                            Console.Write("File is not copied! ");
                        }
                        else
                        {
                            Console.WriteLine($"File \"{name}\" is successfully copied from \"{fileManager.CurrentPath}\" to \"{newDirectory}\"");
                        }
                        
                        Console.WriteLine("Press any key to continue...");
                        Console.ReadKey();
                        Console.Clear();
                        break;
                    }
                    case "8":
                    {
                        Console.Clear();
                        fileManager.ViewTxtFiles();
                        Console.Write("File name: ");
                        string fName = Console.ReadLine();
                        if (!fileManager.CompressFile(fName))
                        {
                            Console.WriteLine($"File \"{fName}\" isn't compressed!");
                        }
                        else
                        {
                            Console.WriteLine($"File \"{fName}\" successfully compressed");
                        }
                       
                        Console.WriteLine("Press any key to continue...");
                        Console.ReadKey();
                        Console.Clear();
                        break;
                    }
                    case "9":
                    {
                        Console.Clear();
                        fileManager.ViewGzFiles();
                        Console.Write("Archive name: ");
                        string aName = Console.ReadLine();
                        if (!fileManager.DecompressFile(aName))
                        {
                            Console.WriteLine($"Archive \"{aName}\" isn't decomressed!");
                        }
                        else
                        {
                            Console.WriteLine($"Archive \"{aName}\" successfully decompressed");
                        }
                        
                        Console.WriteLine("Press any key to continue...");
                        Console.ReadKey();
                        Console.Clear();
                        break;
                    }
                    case "10":
                    {
                        Console.Clear();
                        fileManager.ViewAccessibleFiles();
                        Console.Write("File name: ");
                        string name = Console.ReadLine();
                        if (!fileManager.FileInfo(name))
                        {
                            Console.WriteLine($"File \"{name}\" is not found!");
                        }
                        Console.WriteLine("Press any key to continue...");
                        Console.ReadKey();
                        Console.Clear();
                        break;
                    }
                    case "11":
                    {
                        Console.Clear();
                        fileManager.ViewAccessibleFiles();
                        Console.Write("Enter a file name: ");
                        string fileName = Console.ReadLine();
                        if (!fileManager.DeleteFile(fileName))
                        {
                            Console.Write($"File \"{fileName}\" is not deleted! ");
                        }
                        else
                        {
                            Console.WriteLine($"File \"{fileName}\" is successfully deleted!");
                        }
                        
                        Console.WriteLine("Press any key to continue...");
                        Console.ReadKey();
                        Console.Clear();
                        break;
                    }
                    default:
                        Console.Clear();
                        Console.WriteLine("Invalid input! Press any key to continue...");
                        Console.ReadKey();
                        Console.Clear();
                        break;
                }
                Console.WriteLine();
            }
        }
        //static chooseFile() {}
    }
}