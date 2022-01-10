#ifndef SOLUTION_H
#define SOLUTION_H
#include "queue.h"

class Solution: public Queue
{
public:
   Node* SearchMin();
   void Transfer(Node* min);
};

#endif // SOLUTION_H
