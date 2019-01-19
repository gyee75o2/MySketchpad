#include"include/Tool/FillTool.h"
#include"include/MyPainter.h"
#include<QQueue>
#include<QDebug>

void FillTool::mousePressEvent(QMouseEvent *event){
    QImage *paintingImage = new QImage(*getBaseImage());
    MyPainter painter(paintingImage, getPen());
    painter.scanLineFill(event->localPos().toPoint(), getFillColor());
    setRenderImage(paintingImage);
    setBaseImage(paintingImage);
}

void FillTool::mouseMoveEvent(QMouseEvent *event){
    UNUSED(event);
}

void FillTool::mouseReleaseEvent(QMouseEvent *event){
    UNUSED(event);
}
