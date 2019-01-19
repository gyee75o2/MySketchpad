#ifndef LINE_H
#define LINE_H
#include"include/Shape/Shape.h"
#include"include/Common.h"

class Line:public Shape{
    friend bool clipLine(Line*, int, int, int, int);
public:
    Line(DrawingArea *a);
    ~Line();
    QImage* draw();
    QImage* dispose();
    QVector<QPoint*>& getPoints();
    void pushPoint(QPoint* point);
    void popPoint();
    bool contain(const QPoint &);
    void setDeg(int);
    void setControlPoint(QVector<QPoint*>::iterator, const QPoint&);
    void move(const QPoint& p);
    void addScaleFactor(int factor);

private:
    QVector<QPoint*> originPoints;
};

#endif // LINE_H
