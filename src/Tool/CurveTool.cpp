#include"include/Tool/Curvetool.h"
#include"include/Shape/Curve.h"
CurveTool::CurveTool(DrawingArea *a):Tool(a){
    shape = nullptr;
};

CurveTool::~CurveTool(){

}

void CurveTool::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        if(shape == nullptr){
            shape = new Curve(mDrawingArea);
            dynamic_cast<Curve*>(shape)->pushPoint(event->localPos().toPoint());
        }
        else if(mDrawingArea->editing()){
            if(shape->grabControlPoint(editPoint,event->localPos().toPoint())){
            }
            else if(shape->contain(event->localPos().toPoint())){
                moveStartPoint = event->localPos().toPoint();
                isMoving = true;
            }
            else{
                finish();
                shape = new Curve(mDrawingArea);
                dynamic_cast<Curve*>(shape)->pushPoint(event->localPos().toPoint());
                return;
            }
        }
        else{
            dynamic_cast<Curve*>(shape)->pushPoint(event->localPos().toPoint());
            setRenderImage(shape->draw());
            dynamic_cast<Curve*>(shape)->popPoint();
        }
    }
    else{
        if(shape != nullptr && !mDrawingArea->editing()){
            mDrawingArea->setEditing(true);
            setRenderImage(shape->drawWithControlPoints());
            //addShape(shape);
            //shape = nullptr;
        }
    }
    return;
}

void CurveTool::mouseMoveEvent(QMouseEvent *event){
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
    dynamic_cast<Curve*>(shape)->pushPoint(event->localPos().toPoint());
    setRenderImage(shape->draw());
    dynamic_cast<Curve*>(shape)->popPoint();
    return;
}

void CurveTool::mouseReleaseEvent(QMouseEvent *event){
    isMoving = false;

    if(event->localPos().toPoint() == drawStartPoint){
        delete shape;
        shape = nullptr;
        return;
    }
    if(mDrawingArea->editing())
        return;
    dynamic_cast<Curve*>(shape)->pushPoint(event->localPos().toPoint());
    setRenderImage(shape->draw());
    //setBaseImage(getRenderImage());
}

void CurveTool::finish(){
    if(shape!=nullptr){
        dynamic_cast<Curve*>(shape)->finished = true;
        mDrawingArea->setEditing(false);
        setRenderImage(shape->draw());
        setBaseImage(getRenderImage());
        addShape(shape);
        //delete shape;
        shape = nullptr;
    }
    return;
}
