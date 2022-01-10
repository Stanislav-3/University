#include "solution.h"

Node* Solution::SearchMin()
{
    Node *temp = head;
    Node *min = head;
    bool only;
    int minValue = 300000000;
    while (temp) {
        if (temp->number < minValue) {
            minValue = temp->number;
            only = true;
            min = temp;
        } else if (temp->number == minValue) {
            only = false;
        }
        temp = temp->next;
    }
    if (only) {
        return min;
    } else return nullptr;
}

void Solution::Transfer(Node *min)
{
    if (min->prev) {
        min->prev->next = min->next;
    } else return;
    if (min->next) {
        min->next->prev = min->prev;
    }
    else {
        tail = tail->prev;
    }
    min->next = head;
    min->prev = nullptr;
    head->prev = min;
    head = min;
}
