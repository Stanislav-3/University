#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <polygon.h>
#include <ellipse.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool draw = false;
    int typeFigure = -1;
    enum typeFigure {
      polygon,
      ellipse
    };
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void outDefault();
private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    Polygon *itemPolygon;
    Ellipse *itemEllipse;

private slots:

    void on_Polygon_clicked();
    void on_drawButton_clicked();
    void on_clearButton_clicked();
    void on_Exit_clicked();

    void on_moveCenter_clicked();
    void on_pushButton_clicked();
    void on_Ellipse_clicked();
    void on_pushButton_2_clicked();
};

#endif // MAINWINDOW_H
