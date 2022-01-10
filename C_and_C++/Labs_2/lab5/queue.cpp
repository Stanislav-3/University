#include "queue.h"

Queue::Queue()
{
    head = tail = nullptr;
}

Queue::~Queue()
{
    while(head) {
        tail = head->next;
        delete head;
        head = tail;
    }
}

void Queue::Add()
{
    Node *temp = new Node;
    temp->number = rand() % 50 + 1;
    temp->next = nullptr;
    if (!IsEmpty()) {
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
    }
    else {
        temp->prev = nullptr;
        head = tail = temp;
    }
}

void Queue::Pop()
{
    if (!head) return;
    if (head->next) {
        head->next->prev = nullptr;
    }
    Node *temp = head;
    head = head->next;
    delete(temp);
}

void Queue::View(Ui::MainWindow *ui, QWidget *widget)
{
    if (IsEmpty()) {
        ui->listWidget->clear();
        ui->listWidget->addItem("You have no items yet...");
        QMessageBox::information(widget, "Warning...", "The queue is empty!");
    } else {
        ui->listWidget->clear();
        Node *temp = head;
        int counter = 0;
        ui->listWidget->addItem("№\tNumber");
        while(temp) {
            ui->listWidget->addItem(QString::number(counter) + "\t" + QString::number(temp->number));
            temp = temp->next;
            counter++;
        }
    }
}

void Queue::Delete(int item)
{

    Node *temp = head;
    for(int counter = 0; counter != item; counter++) {
        temp = temp->next;
    }
    if (temp->prev) {
        temp->prev->next = temp->next;
    }
    else {
        head = head->next;
    }
    if (temp->next) {
        temp->next->prev = temp->prev;
    }
    else {
        tail = tail->prev;
    }
    delete(temp);
}

bool Queue::IsEmpty()
{
    if (head == nullptr) {
        return true;
    }
    else {
        return false;
    }
}
