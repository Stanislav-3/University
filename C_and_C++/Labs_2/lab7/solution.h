#ifndef SOLUTION_H
#define SOLUTION_H
#include "hashtable.h"

class Solution: public HashTable
{
public:
    Solution(int m);
    ~Solution();
    void Initialize();
    void Separate(Solution *negHashTable, Solution *posHashTable);
};

#endif // SOLUTION_H
