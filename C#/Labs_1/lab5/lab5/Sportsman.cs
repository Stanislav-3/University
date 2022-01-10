using System;

namespace lab5
{
    public class Sportsman: Student
    {
        public double Strength
        {
            get
            {
                return _strength;
            }
            private set
            {
                if (value < 0)
                {
                    _strength = 0;
                }
                else if (_strength > 100)
                {
                    _strength = 100;
                }
                else
                {
                    _strength = Math.Round(value, 2);
                }
            }
        }
        private double _strength;
    
        public Sportsman(string fullName, string identifier, bool isMale, DateTime dateOfBirth) :
            base(fullName, identifier, isMale, dateOfBirth)
        {
            Strength = 25;
            AddSportSubjects();
        }
    
        public Sportsman(string fullName, string identifier, bool isMale, DateTime dateOfBirth, double strength): 
            base(fullName, identifier, isMale, dateOfBirth)
        {
            Strength = strength;
            AddSportSubjects();
        }
        
        public Sportsman(string fullName, string identifier, bool isMale, DateTime dateOfBirth, int course, double promise): 
            base(fullName, identifier, isMale, dateOfBirth, course, promise)
        {
            Strength = 25;
            AddSportSubjects();
        }
        
        public Sportsman(string fullName, string identifier, bool isMale, DateTime dateOfBirth, int course, double promise, double strength):
            base(fullName, identifier, isMale, dateOfBirth, course, promise)
        {
            Strength = strength;
            AddSportSubjects();
        }

        private void AddSportSubjects()
        {
            _studentInfo.Subjects = new []
            {
                (int) StudySubjects.PhysicalCulture, (int) StudySubjects.Philosophy, (int) StudySubjects.PoliticalScience
            };
        }

        public override string ToString()
        {
            string result = "Sportsman, " + base.ToString() + $", Strength: {Strength} %\nTaken subjects:\n";
            foreach (var subject in _studentInfo.Subjects)
            {
                result += $">{(StudySubjects) subject}\n";
            }
            return result;
        }

        public override void Study(int minutes)
        {
            Random random = new Random();
            Strength += 0.001 * minutes * random.NextDouble();
            base.Study(minutes);
        }
    }
}