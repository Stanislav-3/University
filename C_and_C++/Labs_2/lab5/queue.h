#ifndef QUEUE_H
#define QUEUE_H
#include "node.h"
#include <ui_mainwindow.h>
#include <QString>
#include "QMessageBox"

class Queue
{
public:
    Node *head, *tail;
    Queue();
    ~Queue();
    void Add();
    void Pop();
    void View(Ui::MainWindow *ui, QWidget *widget);
    void Delete(int item);
    bool IsEmpty();
};

#endif // QUEUE_H
