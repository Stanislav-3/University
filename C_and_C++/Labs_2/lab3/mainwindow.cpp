#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Intercity Automated Telephone Exchange app");
    this->setFixedSize(932, 298);
}

MainWindow::~MainWindow()
{
    delete ui;
    list_ITAE *temp;
    while(list) {
        temp = list;
        list = list->next;
        delete temp;
    }
}


void MainWindow::on_exit_clicked()
{
    exit(0);
}

void MainWindow::on_addInfo_clicked()
{
    ui->listWidget->clear();
    ui->listWidget->addItem("outNumber(inNumber) - is the outgoing(incoming) number\ncode is the code of the city(a number)\n{} means \"optional\"\n"
                            "* * * * * * * * * * * * *\n"
                            "* Input templates:  *\n"
                            "* * * * * * * * * * * * *\n"
                            "* Number: +X{XX}(XX{X})XXX-XX-XX\n"
                            "* City: begins with a capital letter\n"
                            "* Date: XX.XX.XXXX\n"
                            "* Time: XX.XX\n"
                            "* Tariff: X{X}{.X{X}}");
    QString newInfo = QInputDialog::getText(this, "Enter info in the following way:", "outNumber inNumber city code date time tariff");
    ui->listWidget->clear();
    ui->listWidget->addItem("There will be usefull information!");
    if (newInfo.size() == 0) return;
    if(!list->addInfo(&list, newInfo)) {
        QMessageBox::critical(this,"", "The input is invalid...");
    }
    ui->listWidget->clear();
    list->viewInfo(list, ui);
}

void MainWindow::on_viewInfo_clicked()
{
    if (!list) {
        ui->listWidget->clear();
        QMessageBox::critical(0, "", "You have no information yet!");
        ui->listWidget->addItem("There will be useful information!\nFirstly fill the base...");
        return;
    }
    list->viewInfo(list, ui);
}

void MainWindow::on_numberWaiver_clicked()
{
    if (!list) {
        QMessageBox::critical(this, "", "You have no items in a base");
        return;
    }
    QString number = QInputDialog::getText(this, "Delete from a base", "Enter an outgoing number");
    if (number.size() == 0) return;
    if (!list->deleteNumber(&list, number)) {
        QMessageBox::critical(this, "", "There's no that number in a base");
    }
    else {
        QMessageBox::information(this, "", "Number is successfully deleted from a base");
        list->viewInfo(list, ui);
    }
}

void MainWindow::on_numberInfo_clicked()
{
    if (!list) {
        QMessageBox::critical(this, "", "You have no items in a base");
        return;
    }
    QString number = QInputDialog::getText(this, "Search info", "Enter a number");
    if (number.size() == 0) return;
    if (!list->searchNumber(list, number, ui)) {
        QMessageBox::critical(this, "", "There's no that number in a base");
    }
    else {
        QMessageBox::information(this, "", "Number is successfully searched");
    }
}

void MainWindow::on_cityInfo_clicked()
{
    if (!list) {
        QMessageBox::critical(this, "", "You have no items in a base");
        return;
    }
    QString city = QInputDialog::getText(this, "Search info", "Enter a city");
    if (city.size() == 0) return;
    if (!list->searchCity(list, city, ui)) {
        QMessageBox::critical(this, "", "There's no that city in a base");
    }
    else {
        QMessageBox::information(this, "", "City is successfully searched");
    }
}
