#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QInputDialog"
#include "QMessageBox"
#include "stack.h"
MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->setFixedSize(361, 280);
    ui->setupUi(this);
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    infixExpression = "a/(b-c)*(d+e)";
    a = 8.6;
    b = 2.4;
    c = 5.1;
    d = 0.3;
    e = 7.9;
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_ChangeValues_clicked()
{
    QString values = QInputDialog::getText(this, "Enter values", "a b c d e {separated by spaces}");
    QStringList valueList = values.split(" ", QString::SkipEmptyParts);
    if (valueList.size() != 5) {
        QMessageBox::critical(this, "", "Invalid input...");
        return;
    }
    QRegExp checkValue("^[+-]?\\d+\\.?\\d*$");
    for (int i = 0; i < 5; i++) {
        if (!checkValue.exactMatch(valueList[i])) {
            QMessageBox::critical(this, "", "Invalid input...");
            return;
        }
    }
    a = valueList[0].toDouble();
    b = valueList[1].toDouble();
    c = valueList[2].toDouble();
    d = valueList[3].toDouble();
    e = valueList[4].toDouble();
}

void MainWindow::on_changeExpression_clicked()
{
    QString expression = QInputDialog::getText(this, "Enter expression {without spaces}", "It must contain 5 variables(a, b, c, d, e) and '+' '-' '*' '/' can be used");
//    QRegExp checkExpression("^[()abcde+-*/]*$");
//    if (!checkExpression.exactMatch(expression)) {
//        QMessageBox::critical(this, "", "Invalid input...");
//        return;
//    }
    infixExpression = expression;
}

void MainWindow::on_Calculate_clicked()
{
    Stack *head = new Stack();
    ui->listWidget->clear();
    ui->listWidget->addItem("Values:");
    ui->listWidget->addItem("a = " + QString::number(a));
    ui->listWidget->addItem("b = " + QString::number(b));
    ui->listWidget->addItem("c = " + QString::number(c));
    ui->listWidget->addItem("d = " + QString::number(d));
    ui->listWidget->addItem("e = " + QString::number(e));
    ui->listWidget->addItem("");
    ui->listWidget->addItem("Infix form expression:");
    ui->listWidget->addItem(infixExpression);
    ui->listWidget->addItem("");
    if (!head->infixToPostfix(head, infixExpression, &postfixExpression)) {
        QMessageBox::critical(this, "", "Expression is invalid...");
    }
    ui->listWidget->addItem("Postfix form expression:");
    ui->listWidget->addItem(postfixExpression);
    ui->listWidget->addItem("");
    ui->listWidget->addItem("Result:");
    ui->listWidget->addItem(head->calculateResult(head, postfixExpression, a, b, c, d, e));
//    head->empty(&head);
}
