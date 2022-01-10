#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(300, 320);
    ui->listWidget->addItem("Hello!");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_View_clicked()
{
    queue.View(ui, this);
}

void MainWindow::on_Add_clicked()
{
    queue.Add();
    queue.View(ui, this);
}

void MainWindow::on_Delete_clicked()
{
    if (queue.IsEmpty()) {
        QMessageBox::information(this, "Warning...", "The queue is empty!");
    }
    else{
        int deleteItem = ui->listWidget->currentRow() - 1;
        if (deleteItem < 0) {
            QMessageBox::StandardButton reply =
                    QMessageBox::question(this, "Attention...", "Delete the firts element?\n(You also can choose the element!)");
            if (reply == QMessageBox::Yes) {
                queue.Pop();
            }
            else return;
        }
        else {
            queue.Delete(deleteItem);
        }
        queue.View(ui, this);
    }
}

void MainWindow::on_Solution_clicked()
{
    QMessageBox::information(this, "Information...", "Task:\nMove the min element to the first position");
    solution.head = queue.head;
    solution.tail = queue.tail;
    if(solution.IsEmpty()) {
        QMessageBox::critical(this, "Attention...", "You need to add some elements firstly");
    }
    else {
        Node* min = solution.SearchMin();
        if(!min) {
            QMessageBox::critical(this, "Error...", "You have no min value");
        }
        else {
            solution.Transfer(min);
            solution.View(ui, this);
        }
    }
    queue.head = solution.head;
    queue.tail = solution.tail;
}

void MainWindow::on_Exit_clicked()
{
    exit(0);
}
