#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "informationwindow.h"
#include "testingwindow.h"

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
    void on_Help_clicked();

    void on_Exit_clicked();

    void on_Information_clicked();

    void on_Testing_clicked();

private:
    Ui::MainWindow *ui;
    InformationWindow *informationWindow;
    TestingWindow *testingWindow;
};
#endif // MAINWINDOW_H
