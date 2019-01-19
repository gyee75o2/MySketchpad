#ifndef CIRCLE_H
#define CIRCLE_H
#include"include/Shape/Shape.h"

class Circle:public Shape{
public:
    Circle(DrawingArea *a);
    ~Circle();
    QImage* draw();
    QImage* drawWithControlPoints();
    void setControlPoint(QVector<QPoint*>::iterator, const QPoint &p);
    void setCenter(QPoint c);
    QPoint getCenter();
    void setRadius(int r);
    int getRadius();
    void move(const QPoint &p);
    bool contain(const QPoint &p);
    void addScaleFactor(int factor);
    QImage *dispose();

private:
    int radius;
};

#endif // CIRCLE_H
