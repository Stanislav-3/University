#ifndef POLYGON_H
#define POLYGON_H

#include <figure.h>

class Polygon: public Figure
{
    Q_OBJECT;

public:
    QVector <QPair<double, double>> vertex;
    void output();
    void view(QGraphicsScene* scene);
    void calculatePerimeter();
    void calculateAreaAndCenter();
    void shift(int dx, int dy, QGraphicsScene* scene);
    void rotatePolygon(double angle, QGraphicsScene* scene);
    void scale(int flag,  QGraphicsScene* scene);
};

#endif // POLYGON_H
