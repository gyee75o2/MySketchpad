#ifndef POLYGONTOOL_H
#define POLYGONTOOL_H

#include"include/Tool/Tool.h"
#include"include/Shape/Polygon.h"

class PolygonTool:public Tool{
public:
    PolygonTool(DrawingArea *a);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void finish();
};

#endif // POLYGONTOOL_H
