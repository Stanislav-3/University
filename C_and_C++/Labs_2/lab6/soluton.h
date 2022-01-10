#ifndef SOLUTON_H
#define SOLUTON_H
#include "node.h"
#include "treeItem.h"

/* Поменять местами информацию, содержащую максимальный и минимальный ключи
 */
class Soluton: public Tree
{
public:
    Node *minKey(Node *currentNode);
    Node *maxKey(Node *currentNode);
    void swap(Node *minKey, Node *maxKey);
};

#endif // SOLUTON_H
