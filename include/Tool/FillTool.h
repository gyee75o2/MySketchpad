#ifndef FILLTOOL_H
#define FILLTOOL_H

#include"include/Tool/Tool.h"

class FillTool:public Tool{
public:
    FillTool(DrawingArea *d):Tool(d){}
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // FILLTOOL_H
