#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <QListWidget>

class HashTable
{
public:
    int m;
    struct Node{
        Node(int data) {
            this->data = data;
            next = nullptr;
        }
        Node *next;
        int data;
    };
    Node *arr[1000] = {0};

    int Encode(int key);
    int Add(int key);
    int Delete(int key);
    Node* Search(int key);
    void Ouput(QListWidget *listWidget);
    void Delete();
};

#endif // HASHTABLE_H
