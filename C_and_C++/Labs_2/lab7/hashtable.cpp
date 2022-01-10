#include "hashtable.h"

int HashTable::Encode(int key)
{
    if (key >= 0) {
        return key % m;
    } else {
        return m + key % m;
    }
}

int HashTable::Add(int key)
{
    if (Search(key)) return 0;
    Node *node = new Node(key);
    node->next = arr[Encode(key)];
    arr[Encode(key)] = node;
    return 1;
}

int HashTable::Delete(int key)
{
    Node *node = arr[Encode(key)];
    if (!node) return 0;
    if (node->data == key) {
        arr[Encode(key)] = node->next;
        delete node;
        return 1;
    }
    else {
        while (node->next) {
            if (node->next->data == key) {
                delete node->next;
                node->next = node->next->next;
                return 1;
            }
            node = node->next;
        }
    }
    return 0;
}

HashTable::Node* HashTable::Search(int key)
{
    Node *node = arr[Encode(key)];
    while (node) {
        if (node->data == key) return node;
        node = node->next;
    }
    return nullptr;
}

void HashTable::Ouput(QListWidget *listWidget)
{
    listWidget->addItem("Table №\tInformation");
    bool isEmty = true;
    for (int i = 0; i < m; i++) {
        if (!arr[i]) continue;
        listWidget->addItem(QString::number(i) + "\t" + QString::number(arr[i]->data));
        for (Node *temp = arr[i]->next; temp; temp = temp->next) {
            listWidget->addItem("↪︎\t" + QString::number(temp->data));
        }
        isEmty = false;
    }
    if (isEmty) {
        listWidget->clear();
        listWidget->addItem("You have no items!\nBut you can add some :)");
    }
}

void HashTable::Delete()
{
    for (int i = 0; i < 1000; i++) {
        if (!arr[i]) continue;
        while (arr[i]) {
            Node *temp = arr[i];
            arr[i] = arr[i]->next;
            delete temp;
        }
    }

}
