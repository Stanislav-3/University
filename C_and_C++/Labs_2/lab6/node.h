#ifndef NODE_H
#define NODE_H
#include <QString>

struct Node {
    Node *left, *right;
    int score;
    QString name;
};
#endif // NODE_H
