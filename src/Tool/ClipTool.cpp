#include"include/Tool/ClipTool.h"
#include"include/DrawingArea.h"
#include"include/Shape/Rectangle.h"
#include"include/Common.h"

ClipTool::ClipTool(DrawingArea *d):Tool(d){
    shape=nullptr;
}

ClipTool::~ClipTool(){}

void ClipTool::mousePressEvent(QMouseEvent *event){
    if(shape==nullptr){
        drawStartPoint = event->localPos().toPoint();
        shape = new Rectangle(mDrawingArea);
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
            shape = new Rectangle(mDrawingArea);
            drawStartPoint = event->localPos().toPoint();
            return;
        }
    }
}

void ClipTool::mouseMoveEvent(QMouseEvent *event){
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
    dynamic_cast<Rectangle*>(shape)->setRect(drawStartPoint, event->localPos().toPoint());
    setRenderImage(shape->draw());
}

void ClipTool::mouseReleaseEvent(QMouseEvent *event){
    UNUSED(event);
    isMoving = false;

    if(mDrawingArea->editing())
        return;
    if(event->localPos().toPoint() == drawStartPoint){
        delete shape;
        shape = nullptr;
        return;
    }
    //setBaseImage(getRenderImage());
    //ellipse->setDeg(30);
    setRenderImage(shape->drawWithControlPoints());
    mDrawingArea->setEditing(true);
    //addShape(ellipse);
}

void ClipTool::finish(){
    if(shape!=nullptr){
        mDrawingArea->setEditing(false);
        QPoint tl = dynamic_cast<Rectangle*>(shape)->topLeft();
        QPoint br = dynamic_cast<Rectangle*>(shape)->bottomRight();
        mDrawingArea->clip(tl, br);
        delete shape;
        shape = nullptr;
    }
    return;
}
