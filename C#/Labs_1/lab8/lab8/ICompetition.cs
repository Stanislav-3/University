namespace lab8
{
    public interface ICompetition<T>
    { 
        double GetAdvantage();
        bool CompeteWith(T opponent);
    }
}