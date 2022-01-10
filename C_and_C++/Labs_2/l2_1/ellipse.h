#ifndef ELLIPSE_H
#define ELLIPSE_H
#include <figure.h>

class Ellipse: public Figure
{
    Q_OBJECT;
public:
  double r1 = 0, r2 = 0;
  double x1, x2, y1, y2, cx1, cy1;
  /* Will store a number of a node(starting from left and then clockwise) */
  int nodeMoved = -1;
  void view(QGraphicsScene* scene);
  void output();
  void calculatePerimiter();
  void calculateAreaAndCenter();
  void shift(int dx, int dy, QGraphicsScene* scene);
  void scale(int flag,  QGraphicsScene* scene);
  void rotateEllipse(double angle, QGraphicsScene* scene);
};

#endif // ELLIPSE_H
