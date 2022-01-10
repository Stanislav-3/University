#include "order.h"
#include "menuitem.h"
#include <QFile>
#include <QTextStream>
#include <string.h>

int Order::Initialization(Order **orders, int &count, MenuItem *menu, int countMenuItems) {
    QFile ordersFile("/Users/stanislav/Desktop/c++/laba2/Orders.txt");
    if (!ordersFile.open(QFile::ReadOnly | QFile::Text)) {
        return 0;
    }
    QTextStream stream(&ordersFile);
    // Count amount of orders
    while (stream.readLine() != "") {
        count++;
    }
    if (count > 1000) {
        return 0;
    }
    stream.seek(0);
    *orders = new Order [1000];
    for (int i = 0; i < count; i++) {
        stream >> (*orders)[i].OrderNumber;
        stream >> (*orders)[i].TableNumber;
        stream >> (*orders)[i].DishName;
        stream >> (*orders)[i].PortionAmount;
    }
    // Count a price using menu & add a "category" field to the database
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < countMenuItems; j++) {
            if (!QString::compare((*orders)[i].DishName, menu[j].Name)) {
                (*orders)[i].Cost = (*orders)[i].PortionAmount * menu[j].Price;
                strcpy((*orders)[i].Category, menu[j].Category);
                break;
            }
        }
    }
    ordersFile.close();
    return 1;
}

void Order::View(Ui::MainWindow *ui, Order *orders, int begin, int end)
{
    ui->listWidget->addItem("Order №\tTable\tDishName\tPortions\tCost");
    for (int i = begin; i <= end; i++) {
        ui->listWidget->addItem(QString(QString::number(orders[i].OrderNumber)) + "\t" + QString(QString::number(orders[i].TableNumber)) +"\t" +
                                QString(orders[i].DishName) + "\t" + QString(QString::number(orders[i].PortionAmount)) + "\t" +
                                QString(QString::number(orders[i].Cost)));
    }
}

int Order::Add(Order *orders, int &countOrders, MenuItem *menu, int countMenuItems, QString newOrder)
{
    if (countOrders == 1000) return 0;
    QStringList ordersList = newOrder.split(" ", QString::SkipEmptyParts);
    if (ordersList.size() != 4) {
        return 0;
    }
    bool isInMenu = false;
    int index = 0;
    for (; index < countMenuItems; index++) {
        if (!QString::compare(ordersList[2], menu[index].Name)) {
            isInMenu = true;
            break;
        }
    }
    if (!isInMenu) return 0;
    orders[countOrders].OrderNumber = QString(ordersList[0]).toInt();
    orders[countOrders].TableNumber = QString(ordersList[1]).toInt();
    strcpy(orders[countOrders].DishName, ordersList[2].toLatin1());
    orders[countOrders].PortionAmount = QString(ordersList[3]).toInt();
    orders[countOrders].Cost = orders[countOrders].PortionAmount * menu[index].Price;
    countOrders++;
    return 1;
}

int Order::Delete(Order *orders, int row, int &countOrders) {
    for (int i = row; i < countOrders - 1; i++) {
        orders[i] = orders[i + 1];
    }
    countOrders--;
    QFile ordersFile("/Users/stanislav/Desktop/c++/laba2/Orders.txt");
    if (!ordersFile.open(QFile::WriteOnly| QFile::Text)) {
        return 0;
    }
    QTextStream stream(&ordersFile);
    for(int i = 0; i < countOrders; i++) {
        stream << orders[i].OrderNumber << " " << orders[i].TableNumber << " " << orders[i].DishName << " " << orders[i].PortionAmount<<"\n";
    }
    ordersFile.close();
    return 1;
}

int Order::Sort(Order *orders, int countOrders) {
    if (!countOrders) {
        return 0;
    }
    for (int i = 0; i < countOrders; i++) {
        for (int j = 0; j < countOrders - i - 1; j++) {
            if (orders[j].Cost < orders[j + 1].Cost) {
                Order temp = orders[j];
                orders[j] = orders[j + 1];
                orders[j + 1] = temp;
            }
        }
    }
    return 1;
}

