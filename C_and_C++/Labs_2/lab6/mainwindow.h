#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "treeItem.h"
#include "soluton.h"
#include <QList>
#include <QInputDialog>
#include <QMessageBox>

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

    void on_Add_clicked();

    void on_Balance_clicked();

    void on_Search_clicked();

    void on_Delete_clicked();

    void on_MySolution_clicked();

private:
    Ui::MainWindow *ui;
    Tree *tree;
    QTreeWidgetItem *item;
    QList <QString> initialInfo = {"Jhon 12", "Mike 52", "Tyler 2", "Sam 7", "Aden 32"};
};
#endif // MAINWINDOW_H
