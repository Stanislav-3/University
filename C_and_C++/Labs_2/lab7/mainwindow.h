#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "hashtable.h"
#include <QMessageBox>
#include <QInputDialog>
#include "solution.h"

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

    void on_Set_clicked();

    void on_Add_clicked();

    void on_Search_clicked();

    void on_Delete_clicked();

    void on_MySolution_clicked();

private:
    Ui::MainWindow *ui;
    HashTable *hashTable;
};
#endif // MAINWINDOW_H
