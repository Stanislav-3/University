using System;

namespace lab6
{
    public class Sportsman: Student, ICompetition<Sportsman>, IParty<Sportsman>, IConvertible
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

        public double GetAdvantage()
        {
            return Promise / 2 + Strength;
        }

        public bool CompeteWith(Sportsman opponent)
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
            Strength *= (1 - percent);
            Promise *= (1 - percent / 10);
        }
        
        public override void Study(int minutes)
        {
            Random random = new Random();
            Strength += 0.001 * minutes * random.NextDouble();
            base.Study(minutes);
        }

        public TypeCode GetTypeCode()
        {
            return Strength.GetTypeCode();
        }

        public bool ToBoolean(IFormatProvider provider)
        {
            return Convert.ToBoolean(Strength);
        }

        public byte ToByte(IFormatProvider provider)
        {
            return Convert.ToByte(Strength);
        }

        public char ToChar(IFormatProvider provider)
        {
            return Convert.ToChar(Strength);
        }

        public DateTime ToDateTime(IFormatProvider provider)
        {
            return Convert.ToDateTime(Strength);
        }

        public decimal ToDecimal(IFormatProvider provider)
        {
            return Convert.ToDecimal(Strength);
        }

        public double ToDouble(IFormatProvider provider)
        {
            return Strength;
        }

        public short ToInt16(IFormatProvider provider)
        {
            return Convert.ToInt16(Strength);
        }

        public int ToInt32(IFormatProvider provider)
        {
            return Convert.ToInt32(Strength);
        }

        public long ToInt64(IFormatProvider provider)
        {
            return Convert.ToInt64(Strength);
        }

        public sbyte ToSByte(IFormatProvider provider)
        {
            return Convert.ToSByte(Strength);
        }

        public float ToSingle(IFormatProvider provider)
        {
            return Convert.ToSingle(Strength);
        }

        public string ToString(IFormatProvider provider)
        {
            return Convert.ToString(Strength);
        }

        public object ToType(Type conversionType, IFormatProvider provider)
        {
            return Convert.ChangeType(Strength, conversionType);
        }

        public ushort ToUInt16(IFormatProvider provider)
        {
            return Convert.ToUInt16(Strength);
        }

        public uint ToUInt32(IFormatProvider provider)
        {
            return Convert.ToUInt32(Strength);
        }

        public ulong ToUInt64(IFormatProvider provider)
        {
            return Convert.ToUInt64(Strength);
        }
    }
}