#include"include/Tool/CircleTool.h"
#include"include/Common.h"

CircleTool::CircleTool(DrawingArea *d):Tool(d){
    shape = nullptr;
}

void CircleTool::mousePressEvent(QMouseEvent *event){
    //center = event->localPos().toPoint();
    if(shape == nullptr){
        shape = new Circle(mDrawingArea);
        dynamic_cast<Circle*>(shape)->setCenter(event->localPos().toPoint());
        drawStartPoint = event->localPos().toPoint();
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
            shape = new Circle(mDrawingArea);
            dynamic_cast<Circle*>(shape)->setCenter(event->localPos().toPoint());
            return;
        }
    }
}

void CircleTool::mouseMoveEvent(QMouseEvent *event){
    /*
    r = distanceOf2Points(event->localPos().toPoint(), center);
    paintingImage = new QImage(*getBaseImage());
    MyPainter painter(paintingImage);
    painter.drawCircle(center.x(),center.y(),r,getPen()->color());
    setRenderImage(paintingImage);
    */
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
    dynamic_cast<Circle*>(shape)->setRadius(distanceOf2Points(event->localPos().toPoint(), dynamic_cast<Circle*>(shape)->getCenter()));
    setRenderImage(shape->draw());
}


void CircleTool::mouseReleaseEvent(QMouseEvent *event){
    UNUSED(event);

    isMoving = false;
    //setBaseImage(paintingImage);
    if(event->localPos() == drawStartPoint&&!mDrawingArea->editing()){
        delete shape;
        shape = nullptr;
        return;
    }
    if(mDrawingArea->editing())
        return;
    if(dynamic_cast<Circle*>(shape)->getRadius() == 0){
        shape=nullptr;
        return;
    }
    setRenderImage(shape->drawWithControlPoints());
    mDrawingArea->setEditing(true);
    //addShape(circle);
}


void CircleTool::finish(){
    if(shape == nullptr)
        return;
    else{
        setRenderImage(shape->draw());
        setBaseImage(getRenderImage());
        mDrawingArea->setEditing(false);
        addShape(shape);
        //delete shape;
        shape = nullptr;
    }
}
