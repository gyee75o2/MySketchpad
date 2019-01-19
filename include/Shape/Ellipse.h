#ifndef ELLIPSE_H
#define ELLIPSE_H
#include"include/Shape/Shape.h"

class Ellipse:public Shape{
public:
    Ellipse(DrawingArea *a);
    QImage* draw();
    void setCenter(QPoint c);
    void setParameter(int rx, int ry);
    QImage* drawWithControlPoints();
    void setControlPoint(QVector<QPoint*>::iterator, const QPoint&);
    void setDeg(int);
    int  getDeg();
    bool contain(const QPoint&);
    void move(const QPoint& p);
    void addScaleFactor(int factor);
    QImage* dispose();

private:
    int rx, ry;
};

#endif // ELLIPSE_H
