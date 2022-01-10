#include "polygon.h"

void Polygon::output()
{
    calculatePerimeter();
    calculateAreaAndCenter();
    outArea->setText(QString::number(area));
    outPerimeter->setText(QString::number(perimiter));
    outCenterX->setText(QString::number((int)centerX));
    outCenterY->setText(QString::number((int)centerY));
    cR = R->text().toInt();
    cG = G->text().toInt();
    cB = B->text().toInt();
    QString vertInfo = "Polygon vertexes:";
    if (!vertex.size()) vertInfo += "\nYou have no vertexes\nyet!";
    for (int i = 0; i < vertex.size(); i++) {
        if (i % 2 == 0) vertInfo += "\n";
        vertInfo += QString("("+ QString::number((int)vertex[i].first) + ","+ QString::number((int)vertex[i].second) +")");
        if ( i == 9) {
            vertInfo += "\nAnd Other...";
            break;
        }
    }
    outputInfo->setText(vertInfo);
}

void Polygon::view(QGraphicsScene* scene)
{
    output();
    scene->clear();
    QBrush brush;
    QPen pen;
    brush.setColor(QColor(cR, cG, cB));
    pen.setColor(QColor(cR, cG, cB));
    QPolygon poly;
    for(int i = 0; i < vertex.size(); i++) {
        vertex[i].first = vertex[i].first * zoom - centerX * zoom + centerX;
        vertex[i].second = vertex[i].second * zoom - centerY * zoom + centerY;
        poly << QPoint(vertex[i].first, vertex[i].second);
        scene->addEllipse(vertex[i].first- 3, vertex[i].second- 3, 6, 6, QPen(Qt::red));
    }
    zoom = 1;
    scene->addPolygon(poly, pen, QBrush(QColor(cR, cG, cB)));
    scene->addEllipse(centerX - 3, centerY - 3, 6, 6, QPen(Qt::red), QBrush(Qt::red));
}

void Polygon::calculatePerimeter()
{
    perimiter = 0;
    int size = vertex.size();
    for (int i = 0; i < size; i++) {
        perimiter += sqrt(pow((vertex[i].first - vertex[(i + 1) % size].first), 2) + pow((vertex[i].second - vertex[(i + 1) % size].second), 2));
    }
}

void Polygon::calculateAreaAndCenter()
{
    area = 0;
    centerX = 0, centerY = 0;
    int size = vertex.size();
    for (int i = 0; i < size; i++) {
        double a = vertex[i].first * vertex[(i + 1) % size].second - vertex[i].second * vertex[(i + 1) % size].first;
        area += a;
        centerX += (vertex[i].first + vertex[(i + 1) % size].first) * a;
        centerY += (vertex[i].second + vertex[(i + 1) % size].second) * a;
    }
    area = abs(area) / 2;
    centerX /= area * 6;
    centerY /= area * 6;
}

void Polygon::shift(int dx, int dy, QGraphicsScene* scene)
{
    int size = vertex.size();
    for (int i = 0; i < size; i++) {
        vertex[i].first += dx;
        vertex[i].second += dy;
    }
    view(scene);
}

void Polygon::rotatePolygon(double angle, QGraphicsScene* scene)
{
    angle = angle / 180 * M_PI;
    int size = vertex.size();
        for(int i = 0; i < size; i++) {
            double x = vertex[i].first, y = vertex[i].second;
            vertex[i].first = (x - centerX) * cos(angle) - (y - centerY) * sin(angle) + centerX;
            vertex[i].second = (x - centerX) * sin(angle) + (y - centerY) * cos(angle) + centerY;
        }
        view(scene);
}

void Polygon::scale(int flag, QGraphicsScene *scene)
{
    if (flag > 0) zoom = 1.01;
    if (flag < 0) zoom = 0.99;
    view(scene);
}
