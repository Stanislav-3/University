using System;
using System.Collections.Generic;
using System.Globalization;

namespace lab6
{
    class Program
    {
        static void Main(string[] args)
        {
            while (true)
            {
                Console.Write("Menu:\n" +
                              "1) Open Engineer's list\n" +
                              "2) Open Humanitarian's list\n" +
                              "3) Open Sportsman's list\n" +
                              "4) Exit\n>>>");
                int menuItem = ReadInt(4);
                Student student;
                switch (menuItem)
                {
                    case 1:
                        // Engineer
                        List<Student> engineers = new List<Student>()
                        {
                            new Engineer("Vasya", "1", true, DateTime.Parse("10/10/2001"), 1, 37, 47),
                            new Engineer("Tom", "2", true, DateTime.Parse("9/07/2002"), 2, 47, 32),
                            new Engineer("Masha", "3", false, DateTime.Parse("9/05/2000"), 3, 65, 53)
                        };
                        while (true)
                        {
                            Console.Write("Menu:\n" +
                                          "1) Show all engineers\n" +
                                          "2) Add an engineer\n" +
                                          "3) Delete an engineer\n" +
                                          "4) Arrange a competition\n" +
                                          "5) Arrange a party\n" +
                                          "6) Sort by names\n" +
                                          "7) Return\n>>>");
                            menuItem = ReadInt(7);
                            if (menuItem == 1)
                            {
                                Console.Clear();
                                if (NoStudents(engineers)) break;
                                Console.Write("Engineers:");
                                foreach (var engineer in engineers)
                                {
                                    Console.WriteLine();
                                    Console.WriteLine(engineer);
                                }
                            }
                            else if (menuItem == 2)
                            {
                                student = EngineerInitialization(engineers);
                                if (student != null)
                                {
                                    engineers.Add(student);
                                    Console.WriteLine("New engineer successfully had been added!");
                                }
                            }
                            else if (menuItem == 3)
                            {
                                if (NoStudents(engineers)) break;
                                Console.Write("Enter engineers' ID you'd like to delete:");
                                string identifier = Console.ReadLine();
                                student = (Student) Search(engineers, identifier);
                                if (student == null)
                                {
                                    Console.WriteLine($"Engineer with ID: {identifier} hasn't been found");
                                }
                                else
                                {
                                    Console.WriteLine($"Engineer with ID: {identifier} has been successfully deleted");
                                    student.Delete();
                                    engineers.Remove(student);
                                }
                            }
                            else if (menuItem == 4)
                            {
                                int k = engineers.Count;
                                if (k == 1)
                                {
                                    Console.WriteLine("Not enough contestants!");
                                }
                                else
                                {
                                    Console.WriteLine("Competition:");
                                }
                                for (int i = 0; i < k; i++)
                                {
                                    for (int j = i + 1; j < k; j++) 
                                    {
                                        Console.Write($"{engineers[i].FullName} vs {engineers[j].FullName} => ");
                                        if (((Engineer) engineers[i]).CompeteWith((Engineer) engineers[j]))
                                        {
                                            Console.WriteLine($"{engineers[i].FullName} wins!");
                                        }
                                        else
                                        {
                                            Console.WriteLine($"{engineers[j].FullName} wins!");
                                        }
                                    }
                                }
                            }
                            else if (menuItem == 5)
                            {
                                if (NoStudents(engineers)) break;
                                Console.Write("Enter engineers' ID you'd like to party:");
                                string identifier = Console.ReadLine();
                                student = (Student) Search(engineers, identifier);
                                if (student == null)
                                {
                                    Console.WriteLine($"Engineer with ID: {identifier} hasn't been found");
                                }
                                else
                                {
                                    double promise = student.Promise;
                                    double intelligencege = ((Engineer) student).Intelligence;
                                    Console.WriteLine($"How many minutes do you want {student.FullName} to party?");
                                    int minutes = ReadInt(1440);
                                    ((Engineer)student).Party(minutes);
                                    Console.WriteLine($"{student.FullName} has lost {Math.Round(promise - student.Promise, 2)}% of promise and " +
                                                      $"{Math.Round(intelligencege - ((Engineer) student).Intelligence, 2)}% of intelligence");
                                }
                            }
                            else if (menuItem == 6)
                            {
                                if (NoStudents(engineers)) break;
                                engineers.Sort();
                                Console.WriteLine("Engineers were successfully sorted by their full names");
                            }
                            else if (menuItem == 7) break;
                        }

                        break;
                    case 2:
                        // Humanitarian
                        List<Student> humanitarians = new List<Student>()
                        {
                            new Humanitarian("Tom", "1", true, DateTime.Parse("10/10/2001"), 1, 37, 67),
                            new Humanitarian("Tanya", "2", false, DateTime.Parse("9/07/2002"), 2, 47, 32),
                            new Humanitarian("Masha", "3", false, DateTime.Parse("9/05/2000"), 3, 65, 53)
                        };
                        while (true)
                        {
                            Console.Write("Menu:\n" +
                                          "1) Show all humanitarians\n" +
                                          "2) Add a humanitarian\n" +
                                          "3) Delete a humanitarian\n" +
                                          "4) Arrange a competition\n" +
                                          "5) Arrange a party\n" +
                                          "6) Sort by names\n" +
                                          "7) Return\n>>>");
                            menuItem = ReadInt(7);
                            if (menuItem == 1)
                            {
                                Console.Clear();
                                if (NoStudents(humanitarians)) break;
                                Console.Write("Humanitarians:");
                                foreach (var humanitarian in humanitarians)
                                {
                                    Console.WriteLine();
                                    Console.WriteLine(humanitarian);
                                }
                            }
                            else if (menuItem == 2)
                            {
                                student = HumanitarianInitialization(humanitarians);
                                if (student != null)
                                {
                                    humanitarians.Add(student);
                                    Console.WriteLine("New humanitarian successfully had been added!");
                                }
                            }
                            else if (menuItem == 3)
                            {
                                if (NoStudents(humanitarians)) break;
                                Console.Write("Enter humanitarians' ID you'd like to delete:");
                                string identifier = Console.ReadLine();
                                student = (Student) Search(humanitarians, identifier);
                                if (student == null)
                                {
                                    Console.WriteLine($"Humanitarian with ID: {identifier} hasn't been found");
                                }
                                else
                                {
                                    Console.WriteLine(
                                        $"Humanitarian with ID: {identifier} has been successfully deleted");
                                    student.Delete();
                                    humanitarians.Remove(student);
                                }
                            }
                            else if (menuItem == 4)
                            {
                                int k = humanitarians.Count;
                                if (k == 1)
                                {
                                    Console.WriteLine("Not enough contestants!");
                                }
                                else
                                {
                                    Console.WriteLine("Competition:");
                                }

                                for (int i = 0; i < k; i++)
                                {
                                    for (int j = i + 1; j < k; j++)
                                    {
                                        Console.Write(
                                            $"{humanitarians[i].FullName} vs {humanitarians[j].FullName} => ");
                                        if (((Humanitarian) humanitarians[i]).CompeteWith((Humanitarian) humanitarians[j]))
                                        {
                                            Console.WriteLine($"{humanitarians[i].FullName} wins!");
                                        }
                                        else
                                        {
                                            Console.WriteLine($"{humanitarians[j].FullName} wins!");
                                        }
                                    }
                                }
                            }
                            else if (menuItem == 5)
                            {
                                if (NoStudents(humanitarians)) break;
                                Console.Write("Enter engineers' ID you'd like to party:");
                                string identifier = Console.ReadLine();
                                student = (Student) Search(humanitarians, identifier);
                                if (student == null)
                                {
                                    Console.WriteLine($"Engineer with ID: {identifier} hasn't been found");
                                }
                                else
                                {
                                    double promise = student.Promise;
                                    double vocabulary = ((Humanitarian) student).Vocabulary;
                                    Console.WriteLine($"How many minutes do you want {student.FullName} to party?");
                                    int minutes = ReadInt(1440);
                                    ((Humanitarian) student).Party(minutes);
                                    Console.WriteLine(
                                        $"{student.FullName} has lost {Math.Round(promise - student.Promise, 2)}% of promise and " +
                                        $"{Math.Round(vocabulary - ((Humanitarian) student).Vocabulary, 2)}% of vocabulary");
                                }
                            }
                            else if (menuItem == 6)
                            {
                                if (NoStudents(humanitarians)) break;
                                humanitarians.Sort();
                                Console.WriteLine("Humanitarians were successfully sorted by their full names");
                            }
                            else if (menuItem == 7) break;
                        }

                        break;
                    case 3:
                        // Sportsman
                        List<Student> sportsmen = new List<Student>()
                        {
                            new Sportsman("Mark", "1", true, DateTime.Parse("10/10/2001"), 1, 37, 23),
                            new Sportsman("Tyler", "2", true, DateTime.Parse("9/07/2002"), 2, 47, 68),
                            new Sportsman("Masha", "3", false, DateTime.Parse("9/05/2000"), 3, 65, 53)
                        };
                        while (true)
                        {
                            Console.Write("Menu:\n" +
                                          "1) Show all sportsmen\n" +
                                          "2) Add a sportsman\n" +
                                          "3) Delete a sportsman\n" +
                                          "4) Arrange a competition\n" +
                                          "5) Arrange a party\n" +
                                          "6) Sort by names\n" +
                                          "7) Return\n>>>");
                            menuItem = ReadInt(7);
                            if (menuItem == 1)
                            {
                                Console.Clear();
                                if (NoStudents(sportsmen)) break;
                                Console.Write("Sportsmen:");
                                foreach (var sportsman in sportsmen)
                                {
                                    Console.WriteLine();
                                    Console.WriteLine(sportsman);
                                }
                            }
                            else if (menuItem == 2)
                            {
                                student = SportsmanInitialization(sportsmen);
                                if (student != null)
                                {
                                    sportsmen.Add(student);
                                    Console.WriteLine("New sportsman successfully had been added!");
                                }
                            }
                            else if (menuItem == 3)
                            {
                                if (NoStudents(sportsmen)) break;
                                Console.Write("Enter sportsman's ID you'd like to delete:");
                                string identifier = Console.ReadLine();
                                student = (Student) Search(sportsmen, identifier);
                                if (student == null)
                                {
                                    Console.WriteLine($"Sportsman with ID: {identifier} hasn't been found");
                                }
                                else
                                {
                                    Console.WriteLine(
                                        $"Sportsman with ID: {identifier} has been successfully deleted");
                                    student.Delete();
                                    sportsmen.Remove(student);
                                }
                            }
                            else if (menuItem == 4)
                            {
                                int k = sportsmen.Count;
                                if (k == 1)
                                {
                                    Console.WriteLine("Not enough contestants!");
                                }
                                else
                                {
                                    Console.WriteLine("Competition:");
                                }

                                for (int i = 0; i < k; i++)
                                {
                                    for (int j = i + 1; j < k; j++)
                                    {
                                        Console.Write(
                                            $"{sportsmen[i].FullName} vs {sportsmen[j].FullName} => ");
                                        if (((Sportsman) sportsmen[i]).CompeteWith((Sportsman) sportsmen[j]))
                                        {
                                            Console.WriteLine($"{sportsmen[i].FullName} wins!");
                                        }
                                        else
                                        {
                                            Console.WriteLine($"{sportsmen[j].FullName} wins!");
                                        }
                                    }
                                }
                            }
                            else if (menuItem == 5)
                            {
                                if (NoStudents(sportsmen)) break;
                                Console.Write("Enter sportsman's ID you'd like to party:");
                                string identifier = Console.ReadLine();
                                student = (Student) Search(sportsmen, identifier);
                                if (student == null)
                                {
                                    Console.WriteLine($"Sportsman with ID: {identifier} hasn't been found");
                                }
                                else
                                {
                                    double promise = student.Promise;
                                    double strength = ((Sportsman) student).Strength;
                                    Console.WriteLine($"How many minutes do you want {student.FullName} to party?");
                                    int minutes = ReadInt(1440);
                                    ((Sportsman) student).Party(minutes);
                                    Console.WriteLine(
                                        $"{student.FullName} has lost {Math.Round(promise - student.Promise, 2)}% of promise and " +
                                        $"{Math.Round(strength - ((Sportsman) student).Strength, 2)}% of strength");
                                }
                            }
                            else if (menuItem == 6)
                            {
                                if (NoStudents(sportsmen)) break;
                                sportsmen.Sort();
                                Console.WriteLine("Sportsmen were successfully sorted by their full names");
                            }
                            else if (menuItem == 7) break;
                        }
                        break;
                    case 4:
                        return;
                }
            }
        }
        
        static int ReadInt(int lastNumber)
        {
            int action;
            while (!int.TryParse(Console.ReadLine(), out action) || action < 1 || action > lastNumber)
            {
                Console.WriteLine("Invalid input...Retry");
            }

            return action;
        }
        
        static bool NoStudents<T>(List<T> list)
        {
            if (list.Count == 0)
            {
                Console.WriteLine("No students has been added yet");
                return true;
            }

            return false;
        }
        
        static object Search(List<Student> list, string identifier)
        {
            foreach (var student in list)
            {
                if (student.Identifier == identifier)
                {
                    return student;
                }
            }

            return null;
        }
        
        static bool RequiredStudentsInitialization(List <Student> list, out string fullName, out string identifier, out bool isMale, out DateTime dayOfBirth)
        {
            fullName = identifier = "";
            isMale = true;
            dayOfBirth = DateTime.Now;
            Console.WriteLine("Enter a full name:");
            fullName = Console.ReadLine();
            if (fullName == "")
            {
                Console.WriteLine("\nInvalid input! You didn't enter anything...");
                return false;
            }
            
            Console.WriteLine("Enter identifier:");
            identifier = Console.ReadLine();
            if (identifier == "")
            {
                Console.WriteLine("\nInvalid input! You didn't enter anything...");
                return false;
            }

            if (Search(list, identifier) != null)
            {
                Console.WriteLine($"Human with ID: {identifier} already exists!");
                return false;
            }
            
            Console.WriteLine("Enter a gender (M - Male | F - Female):");
            string gender = Console.ReadLine();
            if (gender.ToUpper() == "M")
            {
                isMale = true;
            } 
            else if (gender.ToUpper() == "F")
            {
                isMale = false;
            }
            else
            {
                Console.WriteLine("\nInvalid input!");
                return false;
            }

            Console.WriteLine("Enter the day of birth (DD.MM.YYYY):");
            string strDayOfBirth = Console.ReadLine();
            if (!DateTime.TryParseExact(strDayOfBirth, "dd.MM.yyyy", new CultureInfo("en-US"),
                DateTimeStyles.None, out dayOfBirth))
            {
                Console.WriteLine("\nInvalid input!");
                return false;
            }
            
            return true;
        }

        static Engineer EngineerInitialization(List<Student> list)
        {
            if (!RequiredStudentsInitialization(list, out var fullName, out var identifier,
                                                out var isMale, out var dayOfBirth)) return null;
            
            Console.WriteLine("Enter an intelligence coefficient| or leave a blank line");
            int intelligence;
            if (!int.TryParse(Console.ReadLine(), out intelligence) || intelligence < 0 || intelligence > 100)
            {
                return new Engineer(fullName, identifier, isMale, dayOfBirth);
            }
            
            Console.WriteLine("Enter a course number| or leave a blank line");
            int course;
            if (!int.TryParse(Console.ReadLine(), out course) || course < 1 || course > 4)
            {
                return new Engineer(fullName, identifier, isMale, dayOfBirth, intelligence);
            }

            Console.WriteLine("Enter a promise coefficient(0 <= <value> <= 100)| or leave a blank line");
            int promise;
            if (!int.TryParse(Console.ReadLine(), out promise) || promise < 0 || promise > 100)
            {
                return new Engineer(fullName, identifier, isMale, dayOfBirth, intelligence);
            }
            
            return new Engineer(fullName, identifier, isMale, dayOfBirth, course, promise, intelligence);
        }
        
        static Sportsman SportsmanInitialization(List<Student> list)
        {
            if (!RequiredStudentsInitialization(list, out var fullName, out var identifier,
                out var isMale, out var dayOfBirth)) return null;
            
            Console.WriteLine("Enter a strength coefficient(0 <= <value> <= 100)| or leave a blank line");
            int strength;
            if (!int.TryParse(Console.ReadLine(), out strength) || strength < 0 || strength > 100)
            {
                return new Sportsman(fullName, identifier, isMale, dayOfBirth);
            }
            
            Console.WriteLine("Enter a course number| or leave a blank line");
            int course;
            if (!int.TryParse(Console.ReadLine(), out course) || course < 1 || course > 4)
            {
                return new Sportsman(fullName, identifier, isMale, dayOfBirth, strength);
            }

            Console.WriteLine("Enter a promise coefficient(0 <= <value> <= 100)| or leave a blank line");
            int promise;
            if (!int.TryParse(Console.ReadLine(), out promise) || promise < 0 || promise > 100)
            {
                return new Sportsman(fullName, identifier, isMale, dayOfBirth, strength);
            }
            
            return new Sportsman(fullName, identifier, isMale, dayOfBirth, course, promise, strength);
        }
        
        static Humanitarian HumanitarianInitialization(List<Student> list)
        {
            if (!RequiredStudentsInitialization(list, out var fullName, out var identifier,
                out var isMale, out var dayOfBirth)) return null;
            
            Console.WriteLine("Enter a vocabulary coefficient(0 <= <value> <= 100)| or leave a blank line");
            int vocabulary;
            if (!int.TryParse(Console.ReadLine(), out vocabulary) || vocabulary < 0 || vocabulary > 100)
            {
                return new Humanitarian(fullName, identifier, isMale, dayOfBirth);
            }
            
            Console.WriteLine("Enter a course number| or leave a blank line");
            int course;
            if (!int.TryParse(Console.ReadLine(), out course) || course < 1 || course > 4)
            {
                return new Humanitarian(fullName, identifier, isMale, dayOfBirth, vocabulary);
            }

            Console.WriteLine("Enter a promise coefficient(0 <= <value> <= 100)| or leave a blank line");
            int promise;
            if (!int.TryParse(Console.ReadLine(), out promise) || promise < 0 || promise > 100)
            {
                return new Humanitarian(fullName, identifier, isMale, dayOfBirth, vocabulary);
            }
            
            return new Humanitarian(fullName, identifier, isMale, dayOfBirth, course, promise, vocabulary);
        }
    }
}