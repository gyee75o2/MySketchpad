#ifndef ELLIPSETOOL_H
#define ELLIPSETOOL_H

#include"include/Tool/Tool.h"
#include"include/Shape/Ellipse.h"

class EllipseTool:public Tool{
public:
    EllipseTool(DrawingArea *a);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void finish();
};

#endif // ELLIPSETOOL_H
