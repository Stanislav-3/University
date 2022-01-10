#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "menuitem.h"
#include "order.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Exit_clicked();

    void on_View_clicked();

    void on_Sort_clicked();

    void on_ProfitableOrder_clicked();

    void on_PopularDish_clicked();

    void on_Delete_clicked();

    void on_Add_clicked();

private:
    Ui::MainWindow *ui;
    int countMenuItems = 0;
    int countOrders = 0;
    MenuItem *menu;
    Order *orders;
};
#endif // MAINWINDOW_H
