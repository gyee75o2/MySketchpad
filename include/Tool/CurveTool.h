#ifndef CURVETOOL_H
#define CURVETOOL_H

#include"include/Tool/Tool.h"

class CurveTool:public Tool{
public:
    CurveTool(DrawingArea *d);
    ~CurveTool();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void finish();
};

#endif // CURVETOOL_H
