#include "include/Tool/PencilTool.h"
#include "include/MyPainter.h"

#include<qdebug.h>

void PencilTool::mousePressEvent(QMouseEvent *event){
    //qDebug()<<"pencil pressed!";
    drawStartPoint = event->localPos().toPoint();
}

void PencilTool::mouseMoveEvent(QMouseEvent *event){
    //painter.drawLine(drawStartPoint, event->localPos());
    QImage *paintingImage = new QImage(*getBaseImage());
    MyPainter painter(paintingImage, getPen());
    int x1 = drawStartPoint.x(), y1 = drawStartPoint.y(), x2 = event->localPos().toPoint().x(), y2 = event->localPos().toPoint().y();
    painter.drawLine(x1, y1, x2, y2);
    setRenderImage(paintingImage);
    setBaseImage(paintingImage);
    drawStartPoint = event->localPos().toPoint();
}

void PencilTool::mouseReleaseEvent(QMouseEvent *event){
    UNUSED(event);
    return;
}
