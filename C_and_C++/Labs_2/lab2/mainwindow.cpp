#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("Menu");
    ui->comboBox->addItem("Orders");
    ui->Infolabel->setText("It's a restaurant database app\nwith some useful functions\n\nUsing combobox choose the database to see");
    this->setFixedSize(665, 525);
    if (!menu->Initialization(&menu, countMenuItems)) {
        ui->Infolabel->setText("Error!\nThe ""Menu"" file is not open!");
    }
    if (!orders->Initialization(&orders, countOrders, menu, countMenuItems)) {
        ui->Infolabel->setText("Error!\nThe ""Orders"" file is not open!");
    }

}

MainWindow::~MainWindow()
{
    delete ui;
    delete menu;
    delete orders;
}


void MainWindow::on_Exit_clicked()
{
    exit(0);
}


void MainWindow::on_View_clicked()
{
    if (ui->comboBox->currentText() == "Menu") {
        ui->listWidget->clear();
        ui->listWidget->addItem("Menu:");
        ui->Infolabel->setText("Amount of items: " + QString::number(countMenuItems));
        ui->listWidget->addItem("Name\tCategory\tPrice");
        for (int i = 0; i < countMenuItems; i++) {
            if (i && QString::compare(menu[i].Category, menu[i - 1].Category)) {
                ui->listWidget->addItem("\n");
            }
            ui->listWidget->addItem(QString(menu[i].Name) + "\t" + QString(menu[i].Category) + "\t" + QString(QString::number(menu[i].Price)));
        }
    } else {
        ui->listWidget->clear();
        ui->listWidget->addItem("Orders:");
        ui->Infolabel->setText("Amount of orders: " + QString::number(countOrders));
        orders->View(ui, orders, 0, countOrders - 1);
    }
}

void MainWindow::on_Sort_clicked()
{
    if (orders->Sort(orders, countOrders)) {
        ui->Infolabel->setText("Sorted! :)");
    } else {
        ui->Infolabel->setText("You have no orders yet!");
    }
    ui->listWidget->clear();
    ui->listWidget->addItem("Orders:");
    orders->View(ui, orders, 0, countOrders - 1);
}

void MainWindow::on_ProfitableOrder_clicked()
{
    if (!countOrders) {
        ui->Infolabel->setText("You have no orders yet!");
        return;
    }
    ui->listWidget->clear();
    int index = -1;
    double maxCost = 0;
    bool only = 1;
    for (int i = 0; i < countOrders; i++) {
        if (orders[i].Cost > maxCost) {
            maxCost = orders[i].Cost;
            index = i;
            only = 1;
        } else if ((maxCost - orders[i].Cost) < 0.001) {
            only = 0;
        }
    }
    ui->Infolabel->setText("Done! :)");
    if (!only) {
        ui->listWidget->addItem("You got several profitable orders!");
        ui->listWidget->addItem("Order №\tTable\tDishName\tPortions\tCost");
        for (int i = 0; i < countOrders; i++) {
            if ((maxCost - orders[i].Cost) < 0.001) {
                ui->listWidget->addItem(QString(QString::number(orders[i].OrderNumber)) + "\t" + QString(QString::number(orders[i].TableNumber)) +"\t" +
                                        QString(orders[i].DishName) + "\t" + QString(QString::number(orders[i].PortionAmount)) + "\t" +
                                        QString(QString::number(orders[i].Cost)));
            }
        }
    }
    else {
        ui->listWidget->addItem("That's your the most profitable order yet!");
        orders->View(ui, orders, index, index);
    }
}

void dishSearchCategory(Order *orders, int countOrders , const char *category, Ui::MainWindow *ui) {
    int index = -1;
    double maxOrders = 0;
    bool only = 1;
    for (int i = 0; i < countOrders; i++) {
        if (!QString::compare(QString(orders[i].Category), category)) {
            if (orders[i].PortionAmount > maxOrders) {
                maxOrders = orders[i].PortionAmount;
                index = i;
                only = 1;
            } else if ((maxOrders - orders[i].PortionAmount) < 0.001) {
                only = 0;
            }
        }
    }
    if (!maxOrders) {
        ui->listWidget->addItem(QString("You have no orders in ") + QString(category) + QString(" category\n"));
        return;
    }
    if (!only) {
        ui->listWidget->addItem(QString("You got several popular dishes in a ") + QString(category) + QString(" category"));
        ui->listWidget->addItem("Order №\tTable\tDishName\tPortions\tCost");
        for (int i = 0; i < countOrders; i++) {
            if ((maxOrders == orders[i].PortionAmount) && !QString::compare(QString(orders[i].Category), category)) {
                ui->listWidget->addItem(QString(QString::number(orders[i].OrderNumber)) + "\t" + QString(QString::number(orders[i].TableNumber)) +
                                        "\t" + QString(orders[i].DishName) + "\t" + QString(QString::number(orders[i].PortionAmount)) + "\t"
                                        + QString(QString::number(orders[i].Cost)));
            }
        }
        ui->listWidget->addItem("");
    }
    else {
        ui->listWidget->addItem(QString("It's the most popular order in a ") + QString(category) + QString( " category"));
        orders->View(ui, orders, index, index);
        ui->listWidget->addItem("");
    }
}

void MainWindow::on_PopularDish_clicked()
{
    if (!countOrders) {
        ui->Infolabel->setText("You have no orders yet!");
        return;
    }
    QMessageBox msgBox(this);
    msgBox.setText("Choose a category to search in...");
    msgBox.setIcon(QMessageBox::Question);
    msgBox.addButton("Exit", QMessageBox::DestructiveRole);
    QAbstractButton *allCategoriesButton = msgBox.addButton("All categories", QMessageBox::ActionRole);
    QAbstractButton *fruitsButton = msgBox.addButton("Fruits", QMessageBox::ActionRole);
    QAbstractButton *vegetablesButton = msgBox.addButton("Vegetables", QMessageBox::ActionRole);
    QAbstractButton *greensButton = msgBox.addButton("Greens", QMessageBox::ActionRole);
    QAbstractButton *nutsButton = msgBox.addButton("Nuts", QMessageBox::ActionRole);
    ui->Infolabel->setText("Done! :)");
    msgBox.exec();
    if (msgBox.clickedButton() == allCategoriesButton) {
        ui->listWidget->clear();
        dishSearchCategory(orders, countOrders, "Fruits", ui);
        dishSearchCategory(orders, countOrders, "Vegetables", ui);
        dishSearchCategory(orders, countOrders, "Greens", ui);
        dishSearchCategory(orders, countOrders, "Nuts", ui);
    } else if (msgBox.clickedButton() == fruitsButton) {
        ui->listWidget->clear();
        dishSearchCategory(orders, countOrders, "Fruits", ui);
    } else if (msgBox.clickedButton() == vegetablesButton) {
        ui->listWidget->clear();
        dishSearchCategory(orders, countOrders, "Vegetables", ui);
    } else if (msgBox.clickedButton() == greensButton) {
        ui->listWidget->clear();
        dishSearchCategory(orders, countOrders, "Greens", ui);
    } else if (msgBox.clickedButton() == nutsButton) {
        ui->listWidget->clear();
        dishSearchCategory(orders, countOrders, "Nuts", ui);
    }
}

void MainWindow::on_Delete_clicked()
{
    int deleteRow = ui->listWidget->currentRow() - 2;
    if (deleteRow < 0) {
        ui->Infolabel->setText("<-- Choose an order to delete");
        return;
    }
    if (QString::compare(QString(ui->listWidget->item(0)->text()),"Orders:")) {
        ui->Infolabel->setText("It's beyond your reach.\nYou are allowed to alter orders only!");
        return;
    }
    if (!orders->Delete(orders, deleteRow, countOrders)) {
         ui->Infolabel->setText("Error!\nThe ""Orders"" file is not open!");
         return;
    }
    ui->Infolabel->setText("The item was successfully deleted! :)");
    ui->listWidget->clear();
    ui->listWidget->addItem("Orders:");
    orders->View(ui, orders, 0, countOrders - 1);
}

void MainWindow::on_Add_clicked()
{
    QString newOrder = QInputDialog::getText(this, "Enter an order in the following way:", "OrderNumber TableNumber DishName PortionAmount");
    if(!orders->Add(orders, countOrders, menu, countMenuItems, newOrder)) {
        ui->Infolabel->setText("The input is invalid...");
        return;
    }
    ui->Infolabel->setText("The item was successfully added:)");
    // Add a cost to the database
    for (int i = 0; i < countMenuItems; i++) {
        if (!QString::compare(orders[countOrders - 1].DishName, menu[i].Name)) {
            orders[countOrders - 1].Cost = orders[countOrders - 1].PortionAmount * menu[i].Price;
            break;
        }
    }
    ui->listWidget->clear();
    ui->listWidget->addItem("Orders:");
    orders->View(ui, orders, 0, countOrders - 1);
}
