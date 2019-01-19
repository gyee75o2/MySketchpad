#ifndef COMMON_H
#define COMMON_H

#include<QPoint>
#include<QDebug>
#include<QtMath>
#include<QQueue>
#include<QStack>
#include"include/MyPainter.h"

class Line;

int distanceOf2Points(const QPoint& p1, const QPoint& p2);
QPoint rotatePoint(const QPoint &center, const QPoint &p, int deg);
int distanceOfPointToLine(const QPoint& p, const QPoint &p1, const QPoint &p2);
bool clipLine(Line*, int xmin, int xmax, int ymin, int ymax);

#endif // COMMON_H
