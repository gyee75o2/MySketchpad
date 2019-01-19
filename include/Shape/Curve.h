#ifndef CURVE_H
#define CURVE_H

#include "include/Shape/Shape.h"

class Curve:public Shape{
public:
    Curve(DrawingArea *d);
    ~Curve();

    QImage* draw();
    QImage* drawWithControlPoints();
    QImage* dispose();
    void setControlPoint(QVector<QPoint*>::iterator, const QPoint&);
    void setDeg(int);
    int  getDeg();
    bool contain(const QPoint&);
    void move(const QPoint& p);
    void addScaleFactor(int factor);

    void popPoint();
    void pushPoint(const QPoint& p);
    bool finished;

private:
    QVector<QPoint*> originPoints;
};

#endif // CURVE_H
