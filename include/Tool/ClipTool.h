#ifndef CLIPTOOL_H
#define CLIPTOOL_H
#include"include/Tool/Tool.h"

class ClipTool:public Tool{
public:
    ClipTool(DrawingArea *d);
    ~ClipTool();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void finish();
};

#endif // CLIPTOOL_H
