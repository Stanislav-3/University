#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "queue.h"
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
    void on_View_clicked();

    void on_Add_clicked();

    void on_Delete_clicked();

    void on_Solution_clicked();

    void on_Exit_clicked();

private:
    Ui::MainWindow *ui;
    Queue queue;
    Solution solution;
};
#endif // MAINWINDOW_H
