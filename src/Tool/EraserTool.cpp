#include"include/Tool/EraserTool.h"
#include"include/MyPainter.h"

void EraserTool::mousePressEvent(QMouseEvent *event){
    //qDebug()<<"Eraser pressed!";
    drawStartPoint = event->localPos().toPoint();

}

void EraserTool::mouseMoveEvent(QMouseEvent *event){
    //painter.drawLine(drawStartPoint, event->localPos());
    QImage* paintingImage = new QImage(*getBaseImage());
    QPen pen;
    pen.setColor("white");
    pen.setWidth(50);
    MyPainter painter(paintingImage, &pen);
    int x1 = drawStartPoint.x(), y1 = drawStartPoint.y(), x2 = event->localPos().toPoint().x(), y2 = event->localPos().toPoint().y();
    painter.drawLine(x1, y1, x2, y2);
    setRenderImage(paintingImage);
    setBaseImage(paintingImage);
    drawStartPoint = event->localPos().toPoint();
}

void EraserTool::mouseReleaseEvent(QMouseEvent *event){
    UNUSED(event);
    return;
}
