using System;

namespace lab8
{
    public delegate double Transformer(int power);

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
        public delegate void ParameterChangedHandler(string parameter, double pValue, double value);
        public static ParameterChangedHandler ParameterChangedMessage;
        
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
                    throw new Exception("Promise cannot be a negative value");
                }
                else if (value > 100)
                {
                    _promise = 100;
                    throw new Exception("Promise cannot be more than 100");
                }
                else
                {
                    _promise = Math.Round(value, 2);
                }
            }
        }
        private double _promise;
        public virtual void Study(int minutes, Transformer transformer)
        {
            Random random = new Random();
            double pPromise = Promise;
            Promise += transformer(-3) * minutes * random.NextDouble();
            ParameterChangedMessage?.Invoke("Promise", pPromise, Promise);
        }

        public override string ToString()
        {
            return string.Format(base.ToString() + $"\nCourse: {_studentInfo.Course}, Promise: {Promise} %");
        }
    }
}