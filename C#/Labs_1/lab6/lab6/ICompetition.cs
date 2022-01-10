namespace lab6
{
    public interface ICompetition<T>
    { 
        double GetAdvantage();
        bool CompeteWith(T opponent);
    }
}