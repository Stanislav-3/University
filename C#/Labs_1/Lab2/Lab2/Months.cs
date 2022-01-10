using System;
using System.Globalization;

/**
 * С помощью класса DateTime вывести на консоль названия месяцев на французском языке.
 * По желанию обобщить на случай, когда язык задается с клавиатуры.
 */
namespace Lab2
{
    public class Months
    {
        public Months()
        {
            Console.Write("Hello!\nEnter english-language name(e.g. French): ");
            string TwoLetterISOName = EnglishNameToTwoLetterISOName(Console.ReadLine());
            if (TwoLetterISOName == null)
            {
                Console.WriteLine("Invalid input...");
                return;
            }
            DateTime date = new DateTime(2020, 01, 01);
            CultureInfo culture = new CultureInfo(TwoLetterISOName);
            Console.WriteLine("Months names in {0}:", culture.EnglishName);
            for (int i = 0; i < 12; i++)
            {
                Console.WriteLine(date.ToString("MMMM", CultureInfo.GetCultureInfo(culture.ToString())));
                date = date.AddMonths(1);
            }
        }
        
        string EnglishNameToTwoLetterISOName(string englishName)
        {
            if (String.IsNullOrEmpty(englishName))
            {
                return null;
            }
            var neutralCultures = CultureInfo.GetCultures(CultureTypes.NeutralCultures);
            foreach (var culture in neutralCultures)
            {
                if (string.Compare(englishName, culture.EnglishName) == 0)
                {
                    return culture.Name;
                }
            }
            return null;
        }
    }
}