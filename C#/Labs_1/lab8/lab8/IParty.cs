namespace lab8
{
    public interface IParty<T>
    {
        double GetResult(int minutes);
        void Party(int minutes);
    }
}