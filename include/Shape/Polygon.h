#ifndef POLYGON_H
#define POLYGON_H
#include"include/Shape/Shape.h"
#include<QVector>

class Polygon:public Shape{
public:
    Polygon(DrawingArea *a);
    ~Polygon();
    void pushPoint(QPoint* point);
    void popPoint();
    QImage* draw();
    QVector<QPoint*>& getPoints();
    bool contain(const QPoint &);
    void setDeg(int);
    void setControlPoint(QVector<QPoint*>::iterator, const QPoint&);
    void move(const QPoint& p);
    void close();
    void addScaleFactor(int factor);
    bool isClosed;
    QImage* dispose();

private:
    QVector<QPoint*> originPoints;
};

#endif // POLYGON_H
