#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polygon.h"
#include "ellipse.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800, 700);
    scene = new QGraphicsScene();
    itemPolygon = new Polygon();
    itemEllipse = new Ellipse();
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    outDefault();
    scene->setSceneRect(6, 2, 791, 541);
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    itemPolygon->setFlag(QGraphicsItem::ItemIsFocusable, true);
    itemEllipse->setFlag(QGraphicsItem::ItemIsFocusable, true);
    itemPolygon->outArea = ui->Area;
    itemPolygon->outPerimeter = ui->Perimeter;
    itemPolygon->outCenterX = ui->XCoordinate;
    itemPolygon->outCenterY = ui->YCoordinate;
    itemPolygon->outputInfo = ui->infoOutput;
    itemPolygon->R = ui->RColor;
    itemPolygon->G = ui->GColor;
    itemPolygon->B = ui->BColor;

    itemEllipse->outArea = ui->Area;
    itemEllipse->outPerimeter = ui->Perimeter;
    itemEllipse->outCenterX = ui->XCoordinate;
    itemEllipse->outCenterY = ui->YCoordinate;
    itemEllipse->outputInfo = ui->infoOutput;
    itemEllipse->R = ui->RColor;
    itemEllipse->G = ui->GColor;
    itemEllipse->B = ui->BColor;

}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete itemPolygon;
    delete itemEllipse;
}

void MainWindow::on_Polygon_clicked()
{
    itemPolygon->vertex.clear();
    typeFigure = polygon;
    draw = false;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (typeFigure == polygon) {
        bool flagVertexMoved = false;
        int x = event->pos().rx();
        int y = event->pos().ry();
        if (x < 8 || x >788 || y < 4 || y > 538) return;
        if (!draw) {
            itemPolygon->vertex.push_back({x, y});
            scene->addEllipse(x - 3, y - 3, 6, 6, QPen(Qt::red));
        }
        if (draw) {
            int size = itemPolygon->vertex.size();
            /* Move vertexes */
            if (itemPolygon->rememb >= 0) {
                itemPolygon->rememb = -1;
                this->setCursor(QCursor(Qt::ArrowCursor));
                return;
            }
            for (int i = 0; i < size; i++) {
                if (abs(x - itemPolygon->vertex[i].first) <= 3 && abs(y - itemPolygon->vertex[i].second) <= 3) {
                    itemPolygon->rememb = i;
                    flagVertexMoved = true;
                    this->setCursor(QCursor(Qt::ClosedHandCursor));
                }
            }
            while(itemPolygon->rememb >= 0) {
                QPoint xy = mapFromGlobal(QPoint(QCursor::pos()));
                int x = xy.rx();
                int y = xy.ry();
                itemPolygon->vertex[itemPolygon->rememb].first = x;
                itemPolygon->vertex[itemPolygon->rememb].second = y;
                QThread::msleep(3);
                itemPolygon->view(scene);
                QApplication::processEvents();
            }
            if (flagVertexMoved) return;
            /* Move polygon */
            QPoint xy = mapFromGlobal(QPoint(QCursor::pos()));
            int x = xy.rx();
            int y = xy.ry();
            if (itemPolygon->move == 1) {
                this->setCursor(QCursor(Qt::ArrowCursor));
                itemPolygon->move = -1;
                return;
            }
            bool pIn = false;
                for (int i = 0, j = size - 1; i < size; j = i++)
                {
                  if ((((itemPolygon->vertex[i].second <= y) && (y < itemPolygon->vertex[j].second)) || ((itemPolygon->vertex[j].second <= y) &&
                     (y < itemPolygon->vertex[i].second))) && (((itemPolygon->vertex[j].second - itemPolygon->vertex[i].second) != 0) &&
                     (x > ((itemPolygon->vertex[j].first - itemPolygon->vertex[i].first) * (y - itemPolygon->vertex[i].second) /
                           (itemPolygon->vertex[j].second - itemPolygon->vertex[i].second) + itemPolygon->vertex[i].first))))
                      pIn = !pIn;
                }
           if (pIn) {
               itemPolygon->move = 1;
               while (itemPolygon->move == 1) {
                   QPoint xy = mapFromGlobal(QPoint(QCursor::pos()));
                   int x1 = xy.rx();
                   int y1 = xy.ry();
                   itemPolygon->shift(x1 - x, y1 - y, scene);
                   x = x1;
                   y = y1;
                   QThread::msleep(3);
                   this->setCursor(QCursor(Qt::ClosedHandCursor));
                   QApplication::processEvents();
               }
           }
        }
    }
    if (typeFigure == ellipse) {
        if (!draw) {
            if(itemEllipse->x2 && itemEllipse->y2) draw = 1;
            else {
                itemEllipse->x1 = itemEllipse->cx1 = event->pos().rx();
                itemEllipse->y1 = itemEllipse->cy1 = event->pos().ry();
            }
            while (!draw) {
                QPoint xy = mapFromGlobal(QPoint(QCursor::pos()));
                itemEllipse->x2 = xy.rx();
                itemEllipse->y2 = xy.ry();
                itemEllipse->view(scene);
                QApplication::processEvents();
            }
        }
        if (draw) {
            bool flagNodeMoved = false;
            double x = event->pos().rx();
            double y = event->pos().ry();
            if (itemEllipse->nodeMoved >= 0) {
                itemEllipse->nodeMoved = -1;
                this->setCursor(QCursor(Qt::ArrowCursor));
                return;
            }
            if (abs(itemEllipse->centerX - itemEllipse->r2/2 - x) < 3 && abs(itemEllipse->centerY - y) < 3) {
                itemEllipse->nodeMoved = 0;
                flagNodeMoved = true;
                this->setCursor(QCursor(Qt::ClosedHandCursor));
            }
            if (abs(itemEllipse->centerX - x) < 3 && abs(itemEllipse->centerY - itemEllipse->r1/2 - y) < 3) {
                itemEllipse->nodeMoved = 1;
                flagNodeMoved = true;
                this->setCursor(QCursor(Qt::ClosedHandCursor));
            }
            if (abs(itemEllipse->centerX + itemEllipse->r2/2 - x) < 3 && abs(itemEllipse->centerY - y) < 3) {
                itemEllipse->nodeMoved = 2;
                flagNodeMoved = true;
                this->setCursor(QCursor(Qt::ClosedHandCursor));
            }
            if (abs(itemEllipse->centerX - x) < 3 && abs(itemEllipse->centerY + itemEllipse->r1/2 - y) < 3) {
                itemEllipse->nodeMoved = 3;
                flagNodeMoved = true;
                this->setCursor(QCursor(Qt::ClosedHandCursor));
            }

            while(itemEllipse->nodeMoved >= 0) {
                QPoint xy = mapFromGlobal(QPoint(QCursor::pos()));
                int x = xy.rx();
                int y = xy.ry();
                if (itemEllipse->nodeMoved == 0) itemEllipse->cx1 = x;
                if (itemEllipse->nodeMoved == 1) itemEllipse->cy1 = y;
                if (itemEllipse->nodeMoved == 2) itemEllipse->x2 = x;
                if (itemEllipse->nodeMoved == 3) itemEllipse->y2 = y;
                itemEllipse->view(scene);
                QThread::msleep(10);
                QApplication::processEvents();
            }
            if (flagNodeMoved) return;
            /* Move ellipse*/
            if(itemEllipse->move == 1) {
               itemEllipse->move = -1;
               this->setCursor(QCursor(Qt::ArrowCursor));
               return;
            }
//            double x = event->pos().rx();
//            double y = event->pos().ry();
            if (pow((x - itemEllipse->centerX) / (itemEllipse->r2 / 2), 2) +
                pow((y - itemEllipse->centerY) / (itemEllipse->r1 / 2), 2) < 1) {
                itemEllipse->move = 1;
                while (itemEllipse->move == 1) {
                    QPoint xy = mapFromGlobal(QPoint(QCursor::pos()));
                    int x1 = xy.rx();
                    int y1 = xy.ry();
                    itemEllipse->shift(x1 - x, y1 - y, scene);
                    x = x1;
                    y = y1;
                    QThread::msleep(3);
                    this->setCursor(QCursor(Qt::ClosedHandCursor));
                    QApplication::processEvents();
                }
            }
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (!draw) return;
    if (typeFigure == polygon) {
        if (event->key() == Qt::Key_Left) itemPolygon->rotatePolygon(-1, scene);
        if (event->key() == Qt::Key_Right) itemPolygon->rotatePolygon(1, scene);
        if (event->key() == Qt::Key_Down) itemPolygon->scale(-1, scene);
        if (event->key() == Qt::Key_Up) itemPolygon->scale(1, scene);
    }
    if (typeFigure == ellipse) {
        if (event->key() == Qt::Key_Left) {
           itemEllipse->rotateEllipse(-1, scene);
        }
        if (event->key() == Qt::Key_Right) itemEllipse->rotateEllipse(1, scene);
        if (event->key() == Qt::Key_Down) itemEllipse->scale(-1, scene);
        if (event->key() == Qt::Key_Up) itemEllipse->scale(1, scene);
    }
}

void MainWindow::outDefault()
{
    ui->infoOutput->setText("There will be output");
    ui->labelSpecific->setText("Hello! :)\n\nPress (← or →) to rotate\nPress (↑ or ↓) to scale\n\nYou can move figures and\nred nodes!");
    ui->Perimeter->setText("-");
    ui->Area->setText("-");
    ui->XCoordinate->setText("-");
    ui->YCoordinate->setText("-");
}

void MainWindow::on_drawButton_clicked()
{
    if (typeFigure == polygon) {
        if (itemPolygon->vertex.size() < 3) {
            ui->infoOutput->setText("You need 3 vertexes\nat least");
            return;
        }
        itemPolygon->view(scene);
        draw = true;
    }
}

void MainWindow::on_clearButton_clicked()
{
    if (typeFigure == polygon) {
        itemPolygon->vertex.clear();
    }
    if (typeFigure == ellipse) {
        itemEllipse->x1 = itemEllipse->x2 = itemEllipse->y1 = itemEllipse->y2 = 0;
        itemEllipse->r1 = itemEllipse->r2 = 0;
    }
    outDefault();
    scene->clear();
}

void MainWindow::on_Exit_clicked()
{
    exit(0);
}

void MainWindow::on_moveCenter_clicked()
{
    if (typeFigure == polygon) {
        int dx = itemPolygon->outCenterX->text().toInt() - itemPolygon->centerX;
        int dy = itemPolygon->outCenterY->text().toInt() - itemPolygon->centerY;
        itemPolygon->shift(dx, dy, scene);
    }
    if (typeFigure == ellipse) {
        int dx = itemEllipse->outCenterX->text().toInt() - itemEllipse->centerX;
        int dy = itemEllipse->outCenterY->text().toInt() - itemEllipse->centerY;
        itemEllipse->shift(dx, dy, scene);
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (!draw) return;
    if (typeFigure == polygon) {
        double size = itemPolygon->vertex.size();
        double ang = 2 / size * M_PI;
        double averageLength = 0;
        for (int i = 0; i < size; i++) {
            averageLength += sqrt(pow((itemPolygon->vertex[i].first - itemPolygon->centerX), 2) +
                                  pow((itemPolygon->vertex[i].second - itemPolygon->centerY), 2));
        }
        averageLength /= size;
        for (int i = 0; i < size; i++) {
            itemPolygon->vertex[i].first = averageLength * cos(ang * (i + 1)) + itemPolygon->centerX;
            itemPolygon->vertex[i].second = averageLength * sin(ang * (i + 1)) + itemPolygon->centerY;
        }
        itemPolygon->view(scene);
    }
    if (typeFigure == ellipse) {
        double r = (itemEllipse->r1 + itemEllipse->r2) / 4;
        itemEllipse->cx1 = itemEllipse->centerX - r;
        itemEllipse->cy1 = itemEllipse->centerY - r;
        itemEllipse->x2 = itemEllipse->centerX + r;
        itemEllipse->y2 = itemEllipse->centerY + r;
        itemEllipse->view(scene);
    }
}

void MainWindow::on_Ellipse_clicked()
{
    itemEllipse->x1 = itemEllipse->x2 = itemEllipse->y1 = itemEllipse->y2 = itemEllipse->r1 = itemEllipse->r2 = 0;
    typeFigure = ellipse;
    draw = false;
}

void MainWindow::on_pushButton_2_clicked()
{
    if (typeFigure == polygon) {
       itemPolygon->cR = ui->RColor->text().toInt();
        itemPolygon->cG = ui->GColor->text().toInt();
        itemPolygon->cB = ui->BColor->text().toInt();
        itemPolygon->view(scene);
    }
    if (typeFigure == ellipse) {
        itemEllipse->cR = ui->RColor->text().toInt();
        itemEllipse->cG = ui->GColor->text().toInt();
        itemEllipse->cB = ui->BColor->text().toInt();
        itemEllipse->view(scene);
    }
}
