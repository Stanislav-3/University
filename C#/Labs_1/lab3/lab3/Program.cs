using System;
using System.Collections.Generic;
using System.Globalization;

namespace lab3
{
    class Program
    {
        static readonly List<Human> humans = new List<Human>();
        static void Main()
        {
            while (true)
            {
                Console.Write("Menu:\n" +
                              "1) Show all humans\n" + 
                              "2) Add new human(without relatives)\n" +
                              "3) Add new human(with relatives)\n" +
                              "4) Find a human\n" +
                              "5) Remove a human\n" +
                              "6) Sort by full name\n" +
                              "7) Add a parent-child relationship\n" +
                              "8) Arrange a marriage\n" +
                              "9) Arrange a divorce\n" +
                              "10) Exit\n>>>");
                int menuItem;
                while (!int.TryParse(Console.ReadLine(), out menuItem) || menuItem < 1 || menuItem > 10)
                {
                    Console.WriteLine("Invalid input...Retry");
                }
                string identifier;
                Human human;
                switch (menuItem)
                {
                    case 1:
                        Console.Clear();
                        if (noHumans()) break;
                        Console.Write("Humans:");
                        foreach (var person in humans)
                        {
                            Console.WriteLine();
                            Console.WriteLine(person);
                        }

                        break;
                    case 2:
                        human = Initialize(false);
                        if (human == null)
                        {
                            Console.WriteLine("New human hasn't been added");
                        }
                        else
                        {
                            Console.WriteLine("New human has been successfully added");
                            humans.Add(human);
                        }

                        break;
                    case 3:
                        human = Initialize(true);
                        if (human == null)
                        {
                            Console.WriteLine("New human hasn't been added");
                        }
                        else
                        {
                            Console.WriteLine("New human has been successfully added");
                            humans.Add(human);
                        }

                        break;
                    case 4:
                        if (noHumans()) break;
                        Console.Write("Enter human's ID you'd like to search:");
                        identifier = Console.ReadLine();
                        human = Search(identifier);
                        if (human == null)
                        {
                            Console.WriteLine($"Human with ID: {identifier} hasn't been found");
                        }
                        else
                        {
                            Console.WriteLine($"Human with ID: {identifier} has been successfully found");
                            Console.WriteLine(human);
                        }

                        break;
                    case 5:
                        if (noHumans()) break;
                        Console.Write("Enter human's ID you'd like to delete:");
                        identifier = Console.ReadLine();
                        human = Search(identifier);
                        if (human == null)
                        {
                            Console.WriteLine($"Human with ID: {identifier} hasn't been found");
                        }
                        else
                        {
                            Console.WriteLine($"Human with ID: {identifier} has been successfully deleted");
                            human.Delete();
                            humans.Remove(human);
                        }

                        break;
                    case 6:
                        if (noHumans()) break;
                        humans.Sort();
                        Console.WriteLine("Humans were successfully sorted by their full names");
                        break;
                    case 7:
                        if (noHumans()) break;
                        Console.Write("Enter parent's identifier: ");
                        identifier = Console.ReadLine();
                        human = Search(identifier);
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

                        if (human.Partner == humanChild)
                        {
                            Console.WriteLine($"It's restricted! They are married");
                            break;
                        }

                        if (humanChild == human.Father || humanChild == human.Mother)
                        {
                            Console.WriteLine($"It's restricted! Child cannot become a father of his parent");
                            break;
                        }

                        if (humanChild.SetParent(human))
                        {
                            Console.WriteLine($"{human.FullName} successfully became a parent of {humanChild.FullName}");
                        }
                        else
                        {
                            if (human.IsMale)
                            {
                                Console.WriteLine($"Child {humanChild.FullName} has already a father");
                            }
                            else
                            {
                                Console.WriteLine($"Child {humanChild.FullName} has already a mother");
                            }
                        }

                        break;
                    case 8:
                        if (noHumans()) break;
                        Console.Write("Enter one of the partners' identifier: ");
                        identifier = Console.ReadLine();
                        human = Search(identifier);
                        if (human == null)
                        {
                            Console.WriteLine($"Human with ID: {identifier} hasn't been found");
                            break;
                        }

                        Human humanPartner;
                        Console.Write("Enter other partners' identifier: ");
                        identifier = Console.ReadLine();
                        humanPartner = Search(identifier);
                        if (humanPartner == null)
                        {
                            Console.WriteLine($"Human with ID: {identifier} hasn't been found");
                            break;
                        }
                        
                        if (!Human.Marry(human, humanPartner))
                        {
                            Console.WriteLine($"This couple cannot be married");
                            break;
                        }
                        Console.WriteLine($"{human.FullName} & {humanPartner.FullName} are marrieds now!");

                        break;
                    case 9:
                        if (noHumans()) break;
                        Console.Write("Enter human's identifier to divorce: ");
                        identifier = Console.ReadLine();
                        human = Search(identifier);
                        if (human == null)
                        {
                            Console.WriteLine($"Human with ID: {identifier} hasn't been found");
                            break;
                        }

                        if (!human.Divorce())
                        {
                            Console.WriteLine($"This human has no partner");
                            break;
                        }
                        
                        Console.WriteLine($"{human.FullName}  was successfully divorced");
                        break;
                    case 10:
                        return;
                }
            }
        }

        static bool noHumans()
        {
            if (humans.Count == 0)
            {
                Console.WriteLine("No humans has been added yet");
                return true;
            }

            return false;
        }

        static bool RequiredInitialization(out string fullName, out string identifier, out bool isMale, out DateTime dayOfBirth)
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

        static bool AdditionalInitialization(out Human mother, out Human father, out Human partner, out List<Human> children)
        {
            mother = father = partner = null;
            children = new List<Human>();
            Console.WriteLine("Enter mother's identifier (or leave a blank line):");
            string motherIdentifier = Console.ReadLine();
            if (motherIdentifier == "")
            {
                mother = null;
            }
            else
            {
                mother = Search(motherIdentifier);
                if (mother == null)
                {
                    Console.WriteLine("Mother has not been found!");
                }
                else if (mother.IsMale)
                {
                    Console.WriteLine("Error! Mother cannot be a male...");
                    mother = null;
                }
            }
            
            Console.WriteLine("Enter father's identifier (or leave a blank line):");
            string fatherIdentifier = Console.ReadLine();
            if (fatherIdentifier == "")
            {
                father = null;
            }
            else
            {
                father = Search(fatherIdentifier);
                if (father == null)
                {
                    Console.WriteLine("Father has not been found!");
                }
                else if (!father.IsMale)
                {
                    Console.WriteLine("Error! Father cannot be a female...");
                    father = null;
                }
            }
            
            Console.WriteLine("Enter partner's identifier (or leave a blank line):");
            string partnerIdentifier = Console.ReadLine();
            if (partnerIdentifier == "")
            {
                partner = null;
            }
            else
            {
                partner = Search(partnerIdentifier);
                if (partner == null)
                {
                    Console.WriteLine("Partner has not been found!");
                } 
                else if (partner == mother || partner == father)
                {
                    Console.WriteLine("Invalid input...Partner cannot be a parent");
                    partner = null;
                }
            }
            
            string childrenIndetifier;
            Human child;
            while (true)
            {
                Console.WriteLine("Enter child's identifier (or leave a blank line):");
                childrenIndetifier = Console.ReadLine();
                if (childrenIndetifier == "")
                {
                    break;
                }

                child = Search(childrenIndetifier);
                if (child == null)
                {
                    Console.WriteLine("Child has not been found!");
                    continue;
                }

                if (child == mother || child == father)
                {
                    Console.WriteLine("Parent cannot be a child of the same human");
                    continue;
                }

                if (child == partner)
                {
                    Console.WriteLine("Human cannot be married with a child");
                    continue;
                }
                
                children.Add(child);
            }
            return true;
        }

        static Human Initialize(bool withRelatives)
        {
            if (!RequiredInitialization(out var fullName, out var identifier,
                                        out var isMale, out var dayOfBirth)) return null;
            
            if (withRelatives == false)
            {
                return new Human(fullName, identifier, isMale, dayOfBirth);
            }

            if (!AdditionalInitialization(out var mother, out var father, 
                                          out var partner, out var children)) return null;
            
            return new Human(fullName, identifier, isMale, dayOfBirth, mother, father, partner, children);
        }

        static Human Search(string identifier)
        {
            foreach (var human in humans)
            {
                if (human.Identifier == identifier)
                {
                    return human;
                }
            }

            return null;
        }
    }
}