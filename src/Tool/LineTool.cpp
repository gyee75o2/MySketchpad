#include "include/Tool/LineTool.h"
#include "include/MyPainter.h"

LineTool::LineTool(DrawingArea *d):Tool(d){
    shape = nullptr;
}

void LineTool::mousePressEvent(QMouseEvent *event){
    //startPoint = event->localPos().toPoint();
    if(shape == nullptr){
        shape = new Line(mDrawingArea);
        dynamic_cast<Line*>(shape)->pushPoint(new QPoint(event->localPos().toPoint()));
    }
    else if(mDrawingArea->editing()){
        if(shape->grabControlPoint(editPoint,event->localPos().toPoint())){
                ;
        }
        else if(shape->contain(event->localPos().toPoint())){
            moveStartPoint = event->localPos().toPoint();
            isMoving = true;
        }
        else{
            finish();
            shape = new Line(mDrawingArea);
            dynamic_cast<Line*>(shape)->pushPoint(new QPoint(event->localPos().toPoint()));
            return;
        }
    }
}

void LineTool::mouseMoveEvent(QMouseEvent *event){
    if(*dynamic_cast<Line*>(shape)->getPoints()[0] == event->localPos().toPoint()){
        return;
    }
    if(mDrawingArea->editing()){
        if(isMoving){
            shape->move(event->localPos().toPoint()-moveStartPoint);
            moveStartPoint = event->localPos().toPoint();
        }
        else
            shape->setControlPoint(editPoint, event->localPos().toPoint());
        setRenderImage(shape->drawWithControlPoints());
        return;
    }
    dynamic_cast<Line*>(shape)->pushPoint(new QPoint(event->localPos().toPoint()));
    setRenderImage(shape->draw());
    dynamic_cast<Line*>(shape)->popPoint();
}

void LineTool::mouseReleaseEvent(QMouseEvent *event){
    isMoving = false;

    //setBaseImage(paintingImage);
    if(mDrawingArea->editing())
        return;
    if(dynamic_cast<Line*>(shape)->getPoints().size() == 1 &&
            *dynamic_cast<Line*>(shape)->getPoints()[0] == event->localPos().toPoint()){
        shape=nullptr;
        return;
    }
    dynamic_cast<Line*>(shape)->pushPoint(new QPoint(event->localPos().toPoint()));
    QImage* paintingImage = shape->drawWithControlPoints();
    mDrawingArea->setEditing(true);
    setRenderImage(paintingImage);
}

void LineTool::finish(){
    if(shape == nullptr)
        return;
    else{
        mDrawingArea->setEditing(false);
        setRenderImage(shape->draw());
        setBaseImage(getRenderImage());
        addShape(shape);
        shape = nullptr;
    }
}
