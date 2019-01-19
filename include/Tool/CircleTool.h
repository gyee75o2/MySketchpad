#ifndef CIRCLETOOL_H
#define CIRCLETOOL_H

#include"include/Tool/Tool.h"
#include"include/Shape/Circle.h"

class CircleTool:public Tool{
public:
    CircleTool(DrawingArea *d);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void finish();
};

#endif // CIRCLETOOL_H
