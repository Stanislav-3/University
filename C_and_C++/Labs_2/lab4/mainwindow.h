#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString infixExpression;
    QString postfixExpression;
    double a, b, c, d, e;

private slots:
    void on_ChangeValues_clicked();

    void on_changeExpression_clicked();

    void on_Calculate_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
