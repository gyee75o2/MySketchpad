#include "include/Tool/EllipseTool.h"

EllipseTool::EllipseTool(DrawingArea *a):Tool(a){
    shape = nullptr;
}

void EllipseTool::mousePressEvent(QMouseEvent *event){
    if(shape==nullptr){
        drawStartPoint = event->localPos().toPoint();
        shape = new Ellipse(mDrawingArea);
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
            shape = new Ellipse(mDrawingArea);
            drawStartPoint = event->localPos().toPoint();
            return;
        }
    }
}

void EllipseTool::mouseMoveEvent(QMouseEvent *event){
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
    QPoint endPoint = event->localPos().toPoint();
    dynamic_cast<Ellipse*>(shape)->setCenter((drawStartPoint + endPoint) / 2);
    dynamic_cast<Ellipse*>(shape)->setParameter(qAbs((drawStartPoint.x() - endPoint.x())/2), qAbs((drawStartPoint.y()-endPoint.y())/2));
    setRenderImage(shape->draw());
}

void EllipseTool::mouseReleaseEvent(QMouseEvent *event){
    UNUSED(event);
    isMoving = false;
    if(event->localPos().toPoint() == drawStartPoint && !mDrawingArea->editing()){
        delete shape;
        shape = nullptr;
        return;
    }

    if(mDrawingArea->editing())
        return;
    //setBaseImage(getRenderImage());
    //ellipse->setDeg(30);
    setRenderImage(shape->drawWithControlPoints());
    mDrawingArea->setEditing(true);
    //addShape(ellipse);
}

void EllipseTool::finish(){
    if(shape==nullptr){
        return;
    }
    else{
        mDrawingArea->setEditing(false);
        mDrawingArea->setDeg(0);
        setRenderImage(shape->draw());
        setBaseImage(getRenderImage());
        addShape(shape);
        //delete shape;
        shape = nullptr;
    }
}
