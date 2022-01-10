#ifndef ORDER_H
#define ORDER_H
#include "menuitem.h"
#include <QString>
#include <ui_mainwindow.h>

class Order
{
public:
    int OrderNumber;
    int TableNumber;
    char DishName[30] = {0};
    int PortionAmount;
    double Cost;
    char Category[30] = {0};

    int Initialization(Order **orders, int &count, MenuItem *menu, int countMenuItems);
    void View(Ui::MainWindow *ui, Order  *orders, int begin, int end);
    int Add(Order *orders, int &countOrders, MenuItem *menu, int countMenu, QString newOrder);
    int Delete(Order *orders, int row, int &countOrders);
    int Sort(Order  *orders, int countOrders);
};

#endif // ORDER_H
