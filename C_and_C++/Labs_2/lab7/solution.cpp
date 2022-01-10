#include "solution.h"

Solution::Solution(int m)
{
    this->m = m;
}

Solution::~Solution()
{
    Delete();
}

void Solution::Initialize()
{
    for (int i = 0; i < m; i++) {
        Add(rand() % 101 - 50);
    }
}

void Solution::Separate(Solution *negHashTable, Solution *posHashTable)
{
    for (int i = 0; i < m; i++) {
        if (!arr[i]) continue;
        while (arr[i]) {
            if (arr[i]->data < 0) {
                negHashTable->Add(arr[i]->data);
            }
            if (arr[i]->data > 0) {
                posHashTable->Add(arr[i]->data);
            }
            arr[i] = arr[i]->next;
        }
    }
}
