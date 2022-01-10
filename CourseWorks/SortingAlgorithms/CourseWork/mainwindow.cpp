#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Sort algorithms app");
    this->setFixedSize(210, 246);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_Help_clicked()
{
    QMessageBox::information(this, "<Help>", "❖Click <Information> to see the information about sorting algorithms and even more...\n\n"
                                             "❖Click <Tests> to (try and compare) see the results of implemented sort algorithms comparison...\n\n"
                                             "❖Click <Help> ☜ hey, you just there!\n\n"
                                             "❖Click <Exit> to exit the programm| yeah, geniusly...");
}

void MainWindow::on_Exit_clicked()
{
    MainWindow::~MainWindow();
    exit(0);
}

void MainWindow::on_Information_clicked()
{
    hide();
    informationWindow = new InformationWindow(this);
    informationWindow->exec();
    show();
}

void MainWindow::on_Testing_clicked()
{
    hide();
    testingWindow = new TestingWindow(this);
    testingWindow->exec();
    show();
}
