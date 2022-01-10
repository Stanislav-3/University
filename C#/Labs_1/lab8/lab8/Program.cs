using System;
using System.Collections.Generic;
using System.Globalization;
using System.Runtime.InteropServices;

namespace lab8
{
    class Program
    {
        static readonly List<Student> students = new List<Student>();
        static void Main(string[] args)
        {
            bool relationshipNotificationIsOn = false,
                marriageNotificationIsOn = false,
                divorceNotificationIsOn = false;
            Human.PersonalInfoChangedHandler FamilyMessage, MarriageMessage, DivorceMessage ;
            FamilyMessage = MarriageMessage = DivorceMessage = message => Console.WriteLine(message);
            while (true)
            {
                Console.Write("Menu:\n" +
                              "1) Show all students\n" +
                              "2) Add a student\n" +
                              "3) Delete a student\n" +
                              "4) Arrange a study\n" +
                              "5) Change personal info\n" +
                              "6) Change skill handlers\n" +
                              "7) Change personal info handlers\n" +
                              "8) Exit\n>>>");
                int menuItem = ReadInt(8);
                switch (menuItem)
                {
                    case 1:
                        Console.Clear();
                        if (NoStudents()) break;
                        Console.Write("Students:");
                        foreach (var stud in students)
                        {
                            Console.WriteLine();
                            Console.WriteLine(stud);
                        }
                        
                        break;
                    case 2:
                        Student student = null;
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
                                try
                                {
                                    student = StudentInitialization();
                                }
                                catch (Exception e)
                                {
                                    Console.WriteLine(e.Message);
                                }
                                if (student != null)
                                {
                                    students.Add(student);
                                    Console.WriteLine("New student successfully has been added!");
                                }
                                
                                break;
                            case 2:
                                try
                                {
                                    student = EngineerInitialization();
                                }
                                catch (Exception e)
                                {
                                    Console.WriteLine(e.Message);
                                }
                                if (student != null)
                                {
                                    students.Add(student);
                                    Console.WriteLine("New student successfully has been added!");
                                }
                                
                                break;
                            case 3:
                                try
                                {
                                    student = SportsmanInitialization();
                                }
                                catch (Exception e)
                                {
                                    Console.WriteLine(e.Message);
                                }
                                if (student != null)
                                {
                                    students.Add(student);
                                    Console.WriteLine("New student successfully has been added!");
                                }
                                
                                break;
                            case 4:
                                try
                                {
                                    student = HumanitarianInitialization();
                                }
                                catch (Exception e)
                                {
                                    Console.WriteLine(e.Message);
                                }
                                if (student != null)
                                {
                                    students.Add(student);
                                    Console.WriteLine("New student successfully has been added!");
                                }
                                
                                break;
                            case 5:
                                break;
                        }
                        break;
                    case 3:
                        if (NoStudents()) break;
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
                        if (NoStudents()) break;
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
                            Console.WriteLine($"Student with ID: {identifier} has been successfully studied");
                            Transformer transformer = power => Math.Pow(10, power);
                            try
                            { 
                                student.Study(minutes, transformer);
                            }
                            catch (Exception e)
                            {
                                Console.WriteLine(e.Message + "It's assigned to the max(100) coefficient");
                            }
                        }
                        
                        break;
                    case 5:
                        if (NoStudents()) break;
                        Console.Write("Menu:\n" +
                                      "1) Add a parent-child relationship\n" +
                                      "2) Arrange a marriage\n" +
                                      "3) Arrange a divorce\n" +
                                      "4) Return\n>>>");
                        menuItem = ReadInt(4);
                        if (menuItem == 1)
                        {
                            Console.Write("Enter parent's identifier: ");
                            identifier = Console.ReadLine();
                            Human human = Search(identifier);
                            if (human == null)
                            {
                                Console.WriteLine($"Parent with ID: {identifier} hasn't been found");
                                break;
                            }

                            Human humanChild;
                            Console.Write("Enter child's identifier: ");
                            identifier = Console.ReadLine();
                            humanChild = Search(identifier);
                            if (humanChild == null)
                            {
                                Console.WriteLine($"Child with ID: {identifier} hasn't been found");
                                break;
                            }
                            
                            if (!humanChild.SetParent(human))
                            {
                                Console.WriteLine("Error!");
                            }
                        }
                        else if (menuItem == 2)
                        {
                            if (NoStudents()) break;
                            Console.Write("Enter one of the partners' identifier: ");
                            identifier = Console.ReadLine();
                            student = Search(identifier);
                            if (student == null)
                            {
                                Console.WriteLine($"Human with ID: {identifier} hasn't been found");
                                break;
                            }

                            Human studentPartner;
                            Console.Write("Enter other partners' identifier: ");
                            identifier = Console.ReadLine();
                            studentPartner = Search(identifier);
                            if (studentPartner == null)
                            {
                                Console.WriteLine($"Human with ID: {identifier} hasn't been found");
                                break;
                            }
                        
                            if (!Human.Marry(student, studentPartner))
                            {
                                Console.WriteLine($"This couple cannot be married");
                            }
                        }
                        else if (menuItem == 3)
                        {
                            if (NoStudents()) break;
                            Console.Write("Enter student's identifier to divorce: ");
                            identifier = Console.ReadLine();
                            student = Search(identifier);
                            if (student == null)
                            {
                                Console.WriteLine($"Student with ID: {identifier} hasn't been found");
                                break;
                            }

                            if (!student.Divorce())
                            {
                                Console.WriteLine($"This student has no partner");
                            }
                        }
                        
                        break;
                    case 6:
                        Console.Write("Menu:\n" +
                                      "1) Show nothing\n" +
                                      "2) Show changed skills\n" +
                                      "3) Show changed skills in detail\n" +
                                      "4) Return\n>>>");
                        menuItem = ReadInt(4);
                        if (menuItem == 1)
                        {
                            Student.ParameterChangedMessage = null;
                        } 
                        else if (menuItem == 2)
                        {
                            Student.ParameterChangedMessage =
                                (parameter, pValue, value) => Console.WriteLine(parameter + " changed");
                        }
                        else if (menuItem == 3)
                        {
                            Student.ParameterChangedMessage = delegate(string parameter, double pValue, double value)
                            {
                                Console.WriteLine(parameter + $" changed from {pValue} to {value} (difference {Math.Round(value - pValue, 2)})");
                            };
                        }

                            break;
                    case 7:
                        string[] isOn = new string[3];
                        isOn[0] = relationshipNotificationIsOn ? "Remove" : "Add";
                        isOn[1] = marriageNotificationIsOn ? "Remove" : "Add";
                        isOn[2] = divorceNotificationIsOn ? "Remove" : "Add";
                            Console.Write("Menu:\n" +
                                          $"1) {isOn[0]} parent-child relationship notification\n" +
                                          $"2) {isOn[1]} marriage notification\n" +
                                          $"3) {isOn[2]} divorce notification\n" +
                                          "4) Return\n>>>");
                        menuItem = ReadInt(4);
                        if (menuItem == 1)
                        {
                            if (!relationshipNotificationIsOn)
                            {
                                Human.FamilyMessage +=  FamilyMessage;
                                relationshipNotificationIsOn = true;
                            }
                            else
                            {
                                Human.FamilyMessage -=  FamilyMessage;
                                relationshipNotificationIsOn = false;
                            }
                        }
                        else if (menuItem == 2)
                        {
                            if (!marriageNotificationIsOn)
                            {
                                Human.MarriageMessage +=  MarriageMessage;
                                marriageNotificationIsOn = true;
                            }
                            else
                            {
                                Human.MarriageMessage -=  MarriageMessage;
                                marriageNotificationIsOn = false;
                            }
                        }
                        else if (menuItem == 3)
                        {
                            if (!divorceNotificationIsOn)
                            {
                                Human.DivorceMessage += DivorceMessage;
                                divorceNotificationIsOn = true;
                            }
                            else
                            {
                                Human.DivorceMessage -= DivorceMessage;
                                divorceNotificationIsOn = false;
                            }
                        }
                        
                        break;
                    case 8:
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

        static bool NoStudents()
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
            if (!int.TryParse(Console.ReadLine(), out promise))
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
            if (!int.TryParse(Console.ReadLine(), out intelligence))
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
            if (!int.TryParse(Console.ReadLine(), out promise))
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
            if (!int.TryParse(Console.ReadLine(), out strength))
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
            if (!int.TryParse(Console.ReadLine(), out promise))
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
            if (!int.TryParse(Console.ReadLine(), out vocabulary))
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
            if (!int.TryParse(Console.ReadLine(), out promise))
            {
                return new Humanitarian(fullName, identifier, isMale, dayOfBirth, vocabulary);
            }
            
            return new Humanitarian(fullName, identifier, isMale, dayOfBirth, course, promise, vocabulary);
        }
    }
}