using System;
using System.Collections.Generic;

namespace lab5
{
    public class Human : IComparable<Human>
    {
        public string FullName { get; }
        public string Identifier { get; }
        public bool IsMale { get; }
        public DateTime DateOfBirth { get; }
        public Human Partner { get; private set; }
        public Human Mother { get; private set; }
        public Human Father { get; private set; }
        public List<Human> Children = new List<Human>();

        public Human(string fullName, string identifier, bool isMale, DateTime dateOfBirth)
        {
            FullName = fullName;
            Identifier = identifier;
            IsMale = isMale;
            DateOfBirth = dateOfBirth;
        }

        public Human(string fullName, string identifier, bool isMale, DateTime dateOfBirth,
            Human mother, Human father, Human partner, List<Human> children)
        {
            FullName = fullName;
            Identifier = identifier;
            IsMale = isMale;
            DateOfBirth = dateOfBirth;
            Mother = mother;
            Father = father;
            Partner = partner;
            foreach (var child in children)
            {
                Children.Add(child);
            }
            if (Partner != null)
            {
                Partner.Partner = this;
            }
            Mother?.AddChild(this);
            Father?.AddChild(this);
        }

        public int GetAge()
        {
            int age = DateTime.Now.Year - DateOfBirth.Year;
            if (DateTime.Now.DayOfYear < DateOfBirth.DayOfYear) age--;
            return age;
        }

        public static bool Marry(Human human1, Human human2)
        {
            if (human1.Partner != null || human2.Partner != null) return false;
            if (human1.Father == human2 || human1.Mother == human2 ||
                human2.Father == human1 || human2.Mother == human1)
            {
                return false;
            }

            human1.Partner = human2;
            human2.Partner = human1;
            return true;
        }

        public bool Divorce()
        {
            if (Partner == null) return false;
            Partner.Partner = null;
            Partner = null;
            return true;
        }

        public bool SetParent(Human parent)
        {
            if (this.Partner == parent) return false;
            if (parent.Mother == this || parent.Father == this) return false;
            if (parent.IsMale)
            {
                if (Father != null) return false;
                Father = parent;
            }
            else
            {
                if (Mother != null) return false;
                Mother = parent;
            }
            parent.AddChild(this);
            return true;
        }
        
        private void AddChild(Human child)
        {
            Children.Add(child);
        }

        private void RemoveChild(Human child)
        {
            Children.Remove(child);
        }

        public void Delete()
        {
            if (Partner != null)
            {
                Partner.Partner = null;
            }

            Mother?.RemoveChild(this);
            Father?.RemoveChild(this);
            if (IsMale)
            {
                foreach (var child in Children)
                {
                    child.Father = null;
                }
            }
            else
            {
                foreach (var child in Children)
                {
                    child.Mother = null;
                }
            }
        }

        public override string ToString()
        {
            string result = "";
            int age = GetAge();
            result += $"{FullName}, {age} y.o.";
            if (IsMale) 
            {
                result += ", Male"; 
            }
            else
            {
                result += ", Female";
            }
            
            result += $", ID = {Identifier}\n";
            if (Mother != null)
            {
                result += $"Mother - {Mother.FullName}";
            }
            else
            {
                result += $"No info about mother";
            }

            if (Father != null)
            {
                result += $", father - {Father.FullName}";
            }
            else
            {
                result += $", no info about father";
            }

            result += "\n";
            if (Partner != null)
            {
                result += $"Married with {Partner.FullName}";
            }
            else
            {
                result += "Not married";
            }

            if (Children.Count == 0)
            {
                result += ", has no children.";
            }
            else
            {
                result += "\nChildren: ";
                for (int i = 0, j = Children.Count; i < j; i++)
                {
                    result += Children[i].FullName;
                    if (i == j - 1)
                    {
                        result += ".";
                    }
                    else
                    {
                        result += ", ";
                    }
                }
            }

            return result;
        }

        public int CompareTo(Human human)
        {
            return FullName.CompareTo(human.FullName);
        }
    }
}