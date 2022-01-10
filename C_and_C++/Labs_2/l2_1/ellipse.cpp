#include "ellipse.h"


void Ellipse::view(QGraphicsScene *scene)
{
    output();
    scene->clear();
    QBrush brush;
    QPen pen;
    brush.setColor(QColor(cR, cG, cB));
    pen.setColor(QColor(cR, cG, cB));
    zoom = 1;
    scene->addEllipse(x1, y1, r2, r1, pen, QBrush(QColor(cR, cG, cB)));

    scene->addEllipse(centerX - 3, centerY - 3, 6, 6, QPen(Qt::red), QBrush(Qt::red));

    scene->addEllipse(x1 - 3, y1 + r1 / 2 - 3, 6, 6, QPen(Qt::red));
    scene->addEllipse(x2 - 3, y2 - r1 / 2 - 3, 6, 6, QPen(Qt::red));
    scene->addEllipse(x1 + r2 / 2 - 3, y1 - 3, 6, 6, QPen(Qt::red));
    scene->addEllipse(x2 - r2 / 2 - 3, y2 - 3, 6, 6, QPen(Qt::red));
}

void Ellipse::output()
{
    x1 = cx1;
    y1 = cy1;
    if (x1 > x2) {
        double temp = x1;
        x1 = x2;
        x2 = temp;
    } else
    if (y1 > y2) {
        double temp = y1;
        y1 = y2;
        y2 = temp;
    }
    r1 = y2 - y1;
    r2 = x2 - x1;
    calculatePerimiter();
    calculateAreaAndCenter();
    outArea->setText(QString::number(area));
    outPerimeter->setText(QString::number(perimiter));
    outCenterX->setText(QString::number((int)centerX));
    outCenterY->setText(QString::number((int)centerY));
    cR = R->text().toInt();
    cG = G->text().toInt();
    cB = B->text().toInt();
    outputInfo->setText("\n\nEllipse radiuses:\n\nr1 = " + QString::number(r1/2) + "\nr2 = " + QString::number(r2/2));
}

void Ellipse::calculatePerimiter()
{
    perimiter = 4 * ((M_PI * r1 * r2 + abs(r1 - r2)) / (r1 + r2));
}

void Ellipse::calculateAreaAndCenter()
{
    area = M_PI * r1 * r2;
    centerX = x1 + r2 / 2;
    centerY = y1 + r1 / 2;
}

void Ellipse::shift(int dx, int dy, QGraphicsScene *scene)
{
    cx1 += dx;
    cy1 += dy;
    x2 += dx;
    y2 += dy;
    view(scene);
}

void Ellipse::scale(int flag, QGraphicsScene *scene)
{
    if (flag > 0) zoom = 1.01;
    if (flag < 0) zoom = 0.99;
    cx1 = (cx1 - centerX) * zoom + centerX;
    cy1 = (cy1 - centerY) * zoom + centerY;
    x2 = (x2 - centerX) * zoom + centerX;
    y2 = (y2 - centerY) * zoom + centerY;
    view(scene);
}

void Ellipse::rotateEllipse(double angle, QGraphicsScene *scene)
{
    view(scene);
    Q_UNUSED(angle);
}
