#include "soluton.h"



Node * Soluton::minKey(Node *currentNode)
{
    if (currentNode->left) {
        return minKey(currentNode->left);
    }
    return currentNode;
}

Node * Soluton::maxKey(Node *currentNode)
{
    if (currentNode->right) {
        return maxKey(currentNode->right);
    }
    return currentNode;
}

void Soluton::swap(Node *min, Node *max)
{
    if (min == max) return;
    QString buff = min->name;
    min->name = max->name;
    max->name = buff;
}
