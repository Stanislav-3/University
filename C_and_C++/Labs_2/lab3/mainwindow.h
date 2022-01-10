#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "ui_mainwindow.h"
#include <QMainWindow>
#include "list_ITAE.cpp"

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
    void on_exit_clicked();

    void on_addInfo_clicked();

    void on_viewInfo_clicked();

    void on_numberWaiver_clicked();

    void on_numberInfo_clicked();

    void on_cityInfo_clicked();

private:
    Ui::MainWindow *ui;
    list_ITAE *list = NULL;
};
#endif // MAINWINDOW_H
