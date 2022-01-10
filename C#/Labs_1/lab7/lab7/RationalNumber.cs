using System;
using System.Collections.Generic;
using System.Text.RegularExpressions;

namespace lab7
{
    public class RationalNumber: IComparable<RationalNumber>, IEquatable<RationalNumber>, IFormattable
    {
        public long Numerator { get; private set; }
        public long Denominator { get; private set; }

        public RationalNumber(long numerator, long denominator = 1)
        {
            Numerator = numerator;
            Denominator = denominator != 0 ? denominator : 1;
            Simplify();
        }
        
        public RationalNumber(double value)
        {
            RationalNumber r = value;
            Numerator = r.Numerator;
            Denominator = r.Denominator;
        }

        public RationalNumber(string s)
        {
            RationalNumber r = Parse(s);
            Numerator = r.Numerator;
            Denominator = r.Denominator;
        }

        private void Simplify()
        {
            long gcd = Math.Abs(GCD(Numerator, Denominator)) * Math.Sign(Denominator);
            Numerator /= gcd;
            Denominator /= gcd;
        }

        public static long GCD(long a, long b)
        {
            return b == 0 ? a : GCD(b, a % b);
        }

        public static long LCM(long a, long b)
        {
            return a * b / GCD(a, b);
        }

        public static RationalNumber operator -(RationalNumber a)
        {
            return new RationalNumber(-a.Numerator, a.Denominator);
        }
        
        public static RationalNumber operator -(RationalNumber a, RationalNumber b)
        {
            return a + (-b);
        }
        
        public static RationalNumber operator +(RationalNumber a, RationalNumber b)
        {
            long lcm = LCM(a.Denominator, b.Denominator);
            return new RationalNumber(lcm / a.Denominator * a.Numerator + 
                                      lcm / b.Denominator * b.Numerator, lcm);
        }
        
        public static RationalNumber operator --(RationalNumber a)
        {
            return a - 1;
        }
        
        public static RationalNumber operator ++(RationalNumber a)
        {
            return a + 1;
        }
        
        public static RationalNumber operator *(RationalNumber a, RationalNumber b)
        {
            RationalNumber r1 = new RationalNumber(a.Numerator, b.Denominator);
            RationalNumber r2 = new RationalNumber(b.Numerator, a.Denominator);
            return new RationalNumber(r1.Numerator * r2.Numerator, r1.Denominator * r2.Denominator);
        }
        
        public static RationalNumber operator /(RationalNumber a, RationalNumber b)
        {
            return a * b.Flip();
        }

        public static RationalNumber operator %(RationalNumber a, RationalNumber b)
        {
            return a - Abs(a / b).IntPart() * b;
        }
        public RationalNumber Flip()
        {
            if (Numerator == 0)
            {
                throw new DivideByZeroException();
            }
            return new RationalNumber(Denominator, Numerator);
        }

        public long IntPart()
        {
            return Numerator / Denominator;
        }

        public RationalNumber FractPart()
        {
            return new RationalNumber(Numerator % Denominator, Denominator);
        }

        public static RationalNumber Abs(RationalNumber a)
        {
            return new RationalNumber(Math.Abs(a.Numerator), a.Denominator);
        }
        
        public static RationalNumber Pow(RationalNumber a, int n)
        {
            if (n < 0) return Pow(a.Flip(), -n);
            if (n == 0) return 1;
            if (n % 2 == 1) return Pow(a, n - 1) * a;
            var temp = Pow(a, n / 2);
            return temp * temp;
        }

        public int Sign()
        {
            return Math.Sign(Numerator);
        }
        public int CompareTo(RationalNumber b)
        {
            long d1 = Numerator * (LCM(Denominator, b.Denominator) / Denominator);
            long d2 = b.Numerator * (LCM(Denominator, b.Denominator) / b.Denominator);
            if (d1 > d2) return 1;
            else if (d1 < d2) return -1;
            else return 0;
        }
        public bool Equals(RationalNumber otherNumber)
        {
            return Numerator == otherNumber.Numerator && Denominator == otherNumber.Denominator;
        }

        public override bool Equals(object obj)
        {
            return obj is RationalNumber && Equals((RationalNumber)obj);
        }

        public override int GetHashCode()
        {
            return HashCode.Combine(Numerator, Denominator);
        }

        public override string ToString()
        {
            return ToString("s");
        }

        public string ToString(string format, IFormatProvider formatProvider = null)
        {
            if (format == null) format = "s";
            switch (format)
            {
                case "s":
                    return string.Concat(Numerator, "/", Denominator);
                case "m":
                    string result = string.Concat(Math.Abs(Numerator / Denominator), " ",
                        Math.Abs(Numerator % Denominator), "/", Denominator);
                    if (Sign() < 0) result = "-" + result;
                    return result;
                case "d":
                    return RationalNumberToString(Numerator, Denominator);
                default:
                    throw new FormatException("Unknown format error");
            }
        }

        public static string RationalNumberToString(long numerator, long denominator)
        {
            Dictionary<long, int> dict = new Dictionary<long, int>();
            string res = "";
            if (numerator < 0)
            {
                res = "-";
                numerator = -numerator;
            }
            for (int i = 0; i < 30; i++)
            {
                res += numerator / denominator;
                long r = numerator % denominator;
                if (r == 0) return res;
                if (dict.TryGetValue(r, out int ind)) return res.Insert(ind, "(") + ')';
                if (i == 0) res += ".";
                dict.Add(r, res.Length);
                numerator = r * 10;
            }
            return res + "...";
        }
        
        public static bool operator ==(RationalNumber a, RationalNumber b)
        {
            return Equals(a, b);
        }

        public static bool operator !=(RationalNumber a, RationalNumber b)
        {
            return !Equals(a, b);
        }
        
        public static bool operator >(RationalNumber a, RationalNumber b)
        {
            return a.CompareTo(b) == 1;
        }
        
        public static bool operator <(RationalNumber a, RationalNumber b)
        {
            return a.CompareTo(b) == -1;
        }
        
        public static bool operator >=(RationalNumber a, RationalNumber b)
        {
            return a.CompareTo(b) != -1;
        }
        
        public static bool operator <=(RationalNumber a, RationalNumber b)
        {
            return a.CompareTo(b) != 1;
        }
        
        public static RationalNumber Min(RationalNumber a, RationalNumber b)
        {
            return a < b ? a : b;
        }
        
        public static RationalNumber Max(RationalNumber a, RationalNumber b)
        {
            return a > b ? a : b;
        }
        
        public static long Ceiling(RationalNumber a)
        {
            if (a.Denominator == 1 || a.Sign() < 0) return a.IntPart();
            return a.IntPart() + 1;
        }

        public static long Floor(RationalNumber a)
        {
            if (a.Denominator == 1 || a.Sign() > 0) return a.IntPart();
            return a.IntPart() - 1;
        }

        public static long Round(RationalNumber a)
        {
            if (Abs(a.Numerator % a.Denominator * 2) < a.Denominator) return a.IntPart();
            if (a.Sign() > 0) return a.IntPart() + 1;
            return a.IntPart() - 1;
        }
        static public RationalNumber Parse(string s, string format = "s")
        {
            if (!TryParse(format, s, out RationalNumber result)) throw new Exception("Parse error");
            return result;
        }

        public static bool TryParse(string s, out RationalNumber result)
        {
            return TryParse("s", s, out result) || TryParse("m", s, out result) || TryParse("d", s, out result);
        }

        public static bool TryParse(string format, string s, out RationalNumber result)
        {
            s = s.Trim();
            result = default;
            switch (format)
            {
                case "s":
                {
                    string pattern = @"^(-?\d+)\s*[/]\s*(\d+)$";
                    if (!Regex.IsMatch(s, pattern)) return false;
                    Match m = Regex.Match(s, pattern);
                    if (!long.TryParse(m.Groups[1].Value, out long value1)) return false;
                    if (!long.TryParse(m.Groups[2].Value, out long value2) || value2 == 0) return false;
                    result = new RationalNumber(value1, value2);
                    return true;
                }
                case "m":
                {
                    string pattern = @"^(-?)(\d+)\s+(\d+)\s*[/]\s*(\d+)$";
                    if (!Regex.IsMatch(s, pattern)) return false;
                    Match m = Regex.Match(s, pattern);
                    bool isNegative = m.Groups[1].Value == "-";
                    if (!long.TryParse(m.Groups[2].Value, out long value1)) return false;
                    if (!long.TryParse(m.Groups[3].Value, out long value2)) return false;
                    if (!long.TryParse(m.Groups[4].Value, out long value3)) return false;
                    result = value1 + new RationalNumber(value2, value3);
                    if (isNegative) result = -result;
                    return true;
                }
                case "d":
                {
                    return StringToRationalNumber(s, out result);
                }
                default:
                    throw new FormatException("Unknown format error");
            }
        }

        private static bool StringToRationalNumber(string s, out RationalNumber result)
        {
            string pattern = @"^(-?)(\d+)[.](\d*)[(](\d+)[)]$";
            if (Regex.IsMatch(s, pattern))
            {
                if (StringToPeriodicRationalNumber(s, out result)) return true;
                s = s.Replace("(", "");
                s = s.Replace(")", "");
            }
            return StringToSimpleRationalNumber(s, out result);
        }

        static bool StringToPeriodicRationalNumber(string s, out RationalNumber result)
        {
            result = default;
            string pattern = @"^(-?)(\d+)[.](\d*)[(](\d+)[)]$";
            if (!Regex.IsMatch(s, pattern)) return false;
            Match m = Regex.Match(s, pattern);
            bool isNegative = m.Groups[1].Value == "-";
            if (!long.TryParse(m.Groups[2].Value, out long intPart)) return false;
            string sa = m.Groups[3].Value + m.Groups[4].Value;
            string sb = m.Groups[3].Value;
            long a, b;
            if (!long.TryParse(sa, out a)) return false;
            if (sb == "") b = 0;
            else if (!long.TryParse(sb, out b)) return false;
            int n = sa.Length;
            int k = sa.Length - sb.Length;
            if (n > 18) return false;
            result = intPart + new RationalNumber(a - b, long.Parse(new string('9', k) + new string('0', n - k)));
            if (isNegative) result = -result;
            return true;
        }
        
        static bool StringToSimpleRationalNumber(string s, out RationalNumber result)
        {
            result = default;
            string pattern = @"^(-?)(\d+)([.](\d+))?$";
            if (!Regex.IsMatch(s, pattern)) return false;
            Match m = Regex.Match(s, pattern);
            bool isNegative = m.Groups[1].Value == "-";
            if (!long.TryParse(m.Groups[2].Value, out long intPart)) return false;
            string fracPart = m.Groups[4].Value;
            int i = 0;
            long den = 1;
            while (i < fracPart.Length && den <= 1e17)
            {
                intPart *= 10;
                intPart += fracPart[i] - '0';
                den *= 10;
                i++;
            }
            result = (intPart, den);
            if (isNegative) result = -result;
            return true;
        }
        
        public static implicit operator RationalNumber(long a)
        {
            return new RationalNumber(a);
        }

        public static implicit operator RationalNumber((long,long) a)
        {
            return new RationalNumber(a.Item1, a.Item2);
        }

        public static implicit operator RationalNumber(decimal a)
        {
            return Parse(a.ToString(), "d");
        }
        
        public static implicit operator RationalNumber(double a)
        {
            return Parse(a.ToString(), "d");
        }
        
        public static implicit operator RationalNumber(float a)
        {
            return Parse(a.ToString(), "d");
        }
        
        public static explicit operator long(RationalNumber a)
        {
            return a.Numerator / a.Denominator;
        }

        public static explicit operator (long, long)(RationalNumber a)
        {
            return (a.Numerator, a.Denominator);
        }

        public static explicit operator decimal(RationalNumber a)
        {
            return (decimal) a.Numerator / a.Denominator;
        }

        public static explicit operator double(RationalNumber a)
        {
            return (double) a.Numerator / a.Denominator;
        }

        public static explicit operator float (RationalNumber a)
        {
            return (float) a.Numerator / a.Denominator;
        }
    }
}