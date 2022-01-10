using System;

namespace lab6
{
    public class Humanitarian: Student, ICompetition<Humanitarian>, IParty<Humanitarian>
    {
        public double Vocabulary
        {
            get
            {
                return _vocabulary;
            }
            private set
            {
                if (value < 0)
                {
                    _vocabulary = 0;
                }
                else if (_vocabulary > 100)
                {
                    _vocabulary = 100;
                }
                else
                {
                    _vocabulary = Math.Round(value, 2);
                }
            }
        }
        private double _vocabulary;
    
        public Humanitarian(string fullName, string identifier, bool isMale, DateTime dateOfBirth) :
            base(fullName, identifier, isMale, dateOfBirth)
        {
            Vocabulary = 25;
            AddHumanisticSubjects();
        }
    
        public Humanitarian(string fullName, string identifier, bool isMale, DateTime dateOfBirth, double intelligence): 
            base(fullName, identifier, isMale, dateOfBirth)
        {
            Vocabulary = intelligence;
            AddHumanisticSubjects();
        }
        
        public Humanitarian(string fullName, string identifier, bool isMale, DateTime dateOfBirth, int course, double promise): 
            base(fullName, identifier, isMale, dateOfBirth, course, promise)
        {
            Vocabulary = 25;
            AddHumanisticSubjects();
        }
        
        public Humanitarian(string fullName, string identifier, bool isMale, DateTime dateOfBirth, int course, double promise, double intelligence):
            base(fullName, identifier, isMale, dateOfBirth, course, promise)
        {
            Vocabulary = intelligence;
            AddHumanisticSubjects();
        }

        private void AddHumanisticSubjects()
        {
            _studentInfo.Subjects = new []
            {
                (int) StudySubjects.Philosophy, (int) StudySubjects.French, (int) StudySubjects.History
            };
        }

        public override string ToString()
        { 
            string result = "Humanitarian, " + base.ToString() + $", Vocabulary: {Vocabulary} %\nTaken subjects:\n";
            foreach (var subject in _studentInfo.Subjects)
            {
                result += $">{(StudySubjects) subject}\n";
            }
            return result;
        }
        
        public double GetAdvantage()
        {
            return Promise / 2 + Vocabulary;
        }

        public bool CompeteWith(Humanitarian opponent)
        {
            Random random = new Random();
            int myChance = (int)GetAdvantage();
            int opponentsChance = (int) opponent.GetAdvantage();
            return myChance > random.Next( myChance + opponentsChance);
        }
        
        public double GetResult(int minutes)
        {
            Random random = new Random();
            return random.Next( (int) (Promise / 10 + minutes / 15) % 100);
        }

        public void Party(int minutes)
        {
            double percent = GetResult(minutes) / 100;
            Vocabulary *= (1 - percent);
            Promise *= (1 - percent / 10);
        }

        public override void Study(int minutes)
        {
            Random random = new Random();
            Vocabulary += 0.001 * minutes * random.NextDouble();
            base.Study(minutes);
        }

    }
}