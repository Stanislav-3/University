using System;
using System.Collections.Generic;
using System.Globalization;

namespace lab5
{
    class Program
    {
        static readonly List<Student> students = new List<Student>();
        static void Main(string[] args)
        {
            while (true)
            {
                Console.Write("Menu:\n" +
                              "1) Show all students\n" +
                              "2) Add a student\n" +
                              "3) Delete a student\n" +
                              "4) Show subjects\n" +
                              "5) Arrange a study\n" +
                              "6) Exit\n>>>");
                int menuItem = ReadInt(6);
                switch (menuItem)
                {
                    case 1:
                        Console.Clear();
                        if (noStudents()) break;
                        Console.Write("Students:");
                        foreach (var stud in students)
                        {
                            Console.WriteLine();
                            Console.WriteLine(stud);
                        }
                        
                        break;
                    case 2:
                        Student student;
                        Console.Write("Who do you want to add?:\n" +
                                      "1) Just a student\n" +
                                      "2) An engineer\n" +
                                      "3) A sportsman\n" +
                                      "4) A humanitarian\n" +
                                      "5) Return\n>>>");
                        menuItem = ReadInt(5);
                        switch (menuItem)
                        {
                            case 1:
                                student = StudentInitialization();
                                if (student != null)
                                {
                                    students.Add(student);
                                    Console.WriteLine("New student successfully had been added!");
                                }
                                
                                break;
                            case 2:
                                student = EngineerInitialization();
                                if (student != null)
                                {
                                    students.Add(student);
                                    Console.WriteLine("New student successfully had been added!");
                                }
                                
                                break;
                            case 3:
                                student = SportsmanInitialization();
                                if (student != null)
                                {
                                    students.Add(student);
                                    Console.WriteLine("New student successfully had been added!");
                                }
                                
                                break;
                            case 4:
                                student = HumanitarianInitialization();
                                if (student != null)
                                {
                                    students.Add(student);
                                    Console.WriteLine("New student successfully had been added!");
                                }
                                
                                break;
                            case 5:
                                break;
                        }
                        break;
                    case 3:
                        if (noStudents()) break;
                        Console.Write("Enter student's ID you'd like to delete:");
                        string identifier = Console.ReadLine();
                        student = Search(identifier);
                        if (student == null)
                        {
                            Console.WriteLine($"Student with ID: {identifier} hasn't been found");
                        }
                        else
                        {
                            Console.WriteLine($"Student with ID: {identifier} has been successfully deleted");
                            student.Delete();
                            students.Remove(student);
                        }
                        
                        break;
                    case 4:
                        Console.WriteLine("Available subjects in the university:");
                        Student.viewSubjects();
                        
                        break;
                    case 5:
                        if (noStudents()) break;
                        Console.Write("Enter student's ID you'd like to study:");
                        identifier = Console.ReadLine();
                        student = Search(identifier);
                        if (student == null)
                        {
                            Console.WriteLine($"Student with ID: {identifier} hasn't been found");
                        }
                        else
                        {
                            Console.WriteLine($"How many minutes you'd like to study {student.FullName}?");
                            int minutes = ReadInt(1200);
                            student.Study(minutes);
                            Console.WriteLine($"Student with ID: {identifier} has been successfully studied");
                        }
                        break;
                    case 6:
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

        static bool noStudents()
        {
            if (students.Count == 0)
            {
                Console.WriteLine("No students has been added yet");
                return true;
            }

            return false;
        }
        
        static Student Search(string identifier)
        {
            foreach (var student in students)
            {
                if (student.Identifier == identifier)
                {
                    return student;
                }
            }

            return null;
        }

        static Student StudentInitialization()
        {
            Console.WriteLine("Enter a full name:");
            string fullName = Console.ReadLine();
            if (fullName == "")
            {
                Console.WriteLine("\nInvalid input! You didn't enter anything...");
                return null;
            }
            
            Console.WriteLine("Enter identifier:");
            string identifier = Console.ReadLine();
            if (identifier == "")
            {
                Console.WriteLine("\nInvalid input! You didn't enter anything...");
                return null;
            }

            if (Search(identifier) != null)
            {
                Console.WriteLine($"Human with ID: {identifier} already exists!");
                return null;
            }
            
            Console.WriteLine("Enter a gender (M - Male | F - Female):");
            string gender = Console.ReadLine();
            bool isMale;
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
                return null;
            }

            Console.WriteLine("Enter the day of birth (DD.MM.YYYY):");
            string strDayOfBirth = Console.ReadLine();
            DateTime dayOfBirth;
            if (!DateTime.TryParseExact(strDayOfBirth, "dd.MM.yyyy", new CultureInfo("en-US"),
                DateTimeStyles.None, out dayOfBirth))
            {
                Console.WriteLine("\nInvalid input!");
                return null;
            }
            
            Console.WriteLine("Enter a course number| or leave a blank line");
            int course;
            if (!int.TryParse(Console.ReadLine(), out course) || course < 1 || course > 4)
            {
                return new Student(fullName, identifier, isMale, dayOfBirth);
            }

            Console.WriteLine("Enter a promise (0 <= <value> <= 100)| or leave a blank line");
            int promise;
            if (!int.TryParse(Console.ReadLine(), out promise) || promise < 0 || promise > 100)
            {
                return new Student(fullName, identifier, isMale, dayOfBirth);
            }
            
            return new Student(fullName, identifier, isMale, dayOfBirth, course, promise);
        }

        static bool RequiredStudentsInitialization(out string fullName, out string identifier, out bool isMale, out DateTime dayOfBirth)
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

            if (Search(identifier) != null)
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

        static Engineer EngineerInitialization()
        {
            if (!RequiredStudentsInitialization(out var fullName, out var identifier,
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
        
        static Sportsman SportsmanInitialization()
        {
            if (!RequiredStudentsInitialization(out var fullName, out var identifier,
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
        
        static Humanitarian HumanitarianInitialization()
        {
            if (!RequiredStudentsInitialization(out var fullName, out var identifier,
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