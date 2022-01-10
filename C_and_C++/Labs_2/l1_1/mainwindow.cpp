#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <math.h>
#include <QThread>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(580, 300);
}

MainWindow::~MainWindow()
{
    delete ui;
}

class circle{
public:
    int x, y, r = 70;
    void left() {
        if (x > 30) {
            x -= 25;
        }
    }

    void right() {
        if (x < 450) {
            x += 25;
        }
    }
};

class wheel: public circle {
public:
    bool isWheelSpinning = false;
    bool isSpinLeft = true;

    wheel(int x0, int y0) {
        x = x0;
        y = y0;
    }

    void wheelStopSpinning() {
        isWheelSpinning = false;
    }
    void wheelStartSpinning() {
        isWheelSpinning = true;
    }
    void spinLeft() {
        isSpinLeft = true;
    }
    void spinRight() {
        isSpinLeft = false;
    }
} wh(240, 100);


void MainWindow::on_pushButton_clicked()
{
    if (wh.isWheelSpinning) {
        wh.spinLeft();
    }
    wh.left();
    repaint();
}

void MainWindow::on_pushButton_2_clicked()
{
    if (wh.isWheelSpinning) {
        wh.spinRight();
    }
    wh.right();
    repaint();
}

void MainWindow::on_pushButton_3_clicked()
{
    if (wh.isWheelSpinning == false) {
        wh.wheelStartSpinning();
        ui->pushButton_3->setText("STOP!");
        while (wh.isWheelSpinning) {
            if (wh.isSpinLeft) {
                alpha += 0.36;
            }
            else {
                alpha -= 0.36;
            }
            repaint();
            QApplication::processEvents();
        }
    }
    else {
        wh.wheelStopSpinning();
        ui->pushButton_3->setText("GO!");
    }

}

void MainWindow::paintEvent(QPaintEvent *event) {
     QPainter painter(this);
     int r = wh.r;
       painter.setPen(QPen(Qt::black, 3, Qt::SolidLine));
       painter.drawEllipse(wh.x, wh.y, 2 * r, 2 * r);
       QThread::msleep(3);
      if (alpha == 360) {
           alpha = 0;
       }
      if (alpha == 0) {
           alpha = 360;
      }
        painter.setPen(QPen(Qt::black, 1, Qt::SolidLine));
        painter.drawLine(wh.x + r - r * cos(alpha * M_PI / 180), wh.y + r + r * sin(alpha * M_PI / 180),
                         wh.x + r + r * cos(alpha * M_PI / 180), wh.y + r - r * sin(alpha * M_PI / 180));
        painter.drawLine(wh.x + r - r * cos((alpha + 45) * M_PI / 180), wh.y + r + r * sin((alpha + 45) * M_PI / 180),
                         wh.x + r + r * cos((alpha + 45) * M_PI / 180), wh.y + r - r * sin((alpha + 45) * M_PI / 180));
        painter.drawLine(wh.x + r - r * cos((alpha + 90) * M_PI / 180), wh.y + r + r * sin((alpha + 90) * M_PI / 180),
                         wh.x + r + r * cos((alpha + 90) * M_PI / 180), wh.y + r - r * sin((alpha + 90) * M_PI / 180));
        painter.drawLine(wh.x + r - r * cos((alpha + 135) * M_PI / 180), wh.y + r + r * sin((alpha + 135) * M_PI / 180),
                         wh.x + r + r * cos((alpha + 135) * M_PI / 180), wh.y + r - r * sin((alpha + 135) * M_PI / 180));
}
