#ifndef FIGURE_H
#define FIGURE_H
#include <QLabel>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QGraphicsScene>
#include "QVector"
#include <QPoint>
#include <QGraphicsView>
#include <math.h>
#include <QLineEdit>
#include <QKeyEvent>
#include <QThread>
#include <QApplication>

class Figure: public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    QLabel *outArea, *outPerimeter, *outputInfo;
    QLineEdit *R, *G, *B, *outCenterX, *outCenterY;
    int cG, cR, cB;
    double area = 0, perimiter = 0;
    double centerX, centerY;
    double zoom = 1;
    int rememb = -1;
    int move = -1;
    QGraphicsItem *p;
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // FIGURE_H
