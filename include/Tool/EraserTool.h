#ifndef ERASERTOOL_H
#define ERASERTOOL_H

#include"include/Tool/Tool.h"

class EraserTool:public Tool{
public:
    EraserTool(DrawingArea* d):Tool(d){}
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // ERASERTOOL_H
