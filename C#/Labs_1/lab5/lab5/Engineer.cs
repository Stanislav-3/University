using System;

namespace lab5
{
    public class Engineer: Student
    {
        public double Intelligence
        {
            get
            {
                return _intelligence;
            }
            private set
            {
                if (value < 0)
                {
                    _intelligence = 0;
                }
                else if (_intelligence > 100)
                {
                    _intelligence = 100;
                }
                else
                {
                    _intelligence = Math.Round(value, 2);
                }
            }
        }
        private double _intelligence;
    
        public Engineer(string fullName, string identifier, bool isMale, DateTime dateOfBirth) :
            base(fullName, identifier, isMale, dateOfBirth)
        {
            Intelligence = 25;
            AddEngineeringSubjects();
        }
    
        public Engineer(string fullName, string identifier, bool isMale, DateTime dateOfBirth, double intelligence): 
            base(fullName, identifier, isMale, dateOfBirth)
        {
            Intelligence = intelligence;
            AddEngineeringSubjects();
        }
        
        public Engineer(string fullName, string identifier, bool isMale, DateTime dateOfBirth, int course, double promise): 
            base(fullName, identifier, isMale, dateOfBirth, course, promise)
        {
            Intelligence = 25;
            AddEngineeringSubjects();
        }
        
        public Engineer(string fullName, string identifier, bool isMale, DateTime dateOfBirth, int course, double promise, double intelligence):
            base(fullName, identifier, isMale, dateOfBirth, course, promise)
        {
            Intelligence = intelligence;
            AddEngineeringSubjects();
        }

        private void AddEngineeringSubjects()
        {
            _studentInfo.Subjects = new []
            {
                (int) StudySubjects.Mathematics, (int) StudySubjects.IT, (int) StudySubjects.English
            };
        }

        public override string ToString()
        { 
            string result = "Engineer, " + base.ToString() + $", Intelligence: {Intelligence} %\nTaken subjects:\n";
            foreach (var subject in _studentInfo.Subjects)
            {
                result += $">{(StudySubjects) subject}\n";
            }
            return result;
        }

        public override void Study(int minutes)
        {
            Random random = new Random();
            Intelligence += 0.001 * minutes * random.NextDouble();
            base.Study(minutes);
        }
    }
}