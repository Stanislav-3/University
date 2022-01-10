using System;

namespace lab6
{
    public enum StudyCourse
    {
        Freshman = 1,
        Sophomore,
        Junior,
        Senior
    }
        
    public enum StudySubjects
    {
            Philosophy = 1,
            PhysicalCulture,
            PoliticalScience,
            History,
            English,
            French,
            Mathematics,
            IT
    }

    public class Student: Human
    {
        public Student(string fullName, string identifier, bool isMale, DateTime dateOfBirth): 
            base(fullName, identifier, isMale, dateOfBirth)
        {
            Promise = 25;
            _studentInfo.Course = StudyCourse.Freshman;
        }

        public StudentInfo _studentInfo;
        
        public Student(string fullName, string identifier, bool isMale, DateTime dateOfBirth, int course, double promise): 
            base(fullName, identifier, isMale, dateOfBirth)
        {
            Promise = promise;
            _studentInfo.Course = (StudyCourse)course;
        }

        public struct StudentInfo
        {
            public StudyCourse Course;
            public int [] Subjects;
        }

        public static void viewSubjects()
        {
            foreach (var subject in Enum.GetValues(typeof(StudySubjects)))
            {
                Console.WriteLine((StudySubjects)subject);
            }
        }

        public double Promise
        {
            get
            {
                return _promise;
            }
            set
            {
                if (value < 0)
                {
                    _promise = 0;
                }
                else if (value > 100)
                {
                    _promise = 100;
                }
                else
                {
                    _promise = Math.Round(value, 2);
                }
            }
        }
        private double _promise;

        public virtual void Study(int minutes)
        {
            Random random = new Random();
            Promise += 0.0001 * minutes * random.NextDouble();
        }

        public override string ToString()
        {
            string gender;
            if (IsMale)
            {
                gender = "Male";
            }
            else
            {
                gender = "Female";
            }

            return string.Format($"{FullName}, ID: {Identifier}, {gender}, Date of Birth: {DateOfBirth.Date.ToString("d")}\n" +
                                 $"Course: {_studentInfo.Course}, Promise: {Promise} %");
        }
    }
}