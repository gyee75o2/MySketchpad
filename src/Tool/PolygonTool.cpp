#include"include/Tool/PolygonTool.h"
#include"include/Common.h"

PolygonTool::PolygonTool(DrawingArea *a):Tool(a){
    shape = nullptr;
};

void PolygonTool::mousePressEvent(QMouseEvent *event){
    if(shape == nullptr){
        shape = new Polygon(mDrawingArea);
        dynamic_cast<Polygon*>(shape)->pushPoint(new QPoint(event->localPos().toPoint()));
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
            shape = new Polygon(mDrawingArea);
            dynamic_cast<Polygon*>(shape)->pushPoint(new QPoint(event->localPos().toPoint()));
            return;
        }
    }
    else{
        if((*(*(dynamic_cast<Polygon*>(shape)->getPoints().end()-1))-event->localPos().toPoint()).manhattanLength()<3){
            return;
        }
        dynamic_cast<Polygon*>(shape)->pushPoint(new QPoint(event->localPos().toPoint()));
        setRenderImage(shape->draw());
        dynamic_cast<Polygon*>(shape)->popPoint();
    }
    return;
}

void PolygonTool::mouseMoveEvent(QMouseEvent *event){
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
    dynamic_cast<Polygon*>(shape)->pushPoint(new QPoint(event->localPos().toPoint()));
    setRenderImage(shape->draw());
    dynamic_cast<Polygon*>(shape)->popPoint();
    return;
}

void PolygonTool::mouseReleaseEvent(QMouseEvent *event){
    isMoving = false;

    if(mDrawingArea->editing())
        return;
    if((event->localPos().toPoint()- *dynamic_cast<Polygon*>(shape)->getPoints()[0]).manhattanLength()<20){
        if(dynamic_cast<Polygon*>(shape)->getPoints().size()==1){
            QImage* renderImage = new QImage(*getBaseImage());
            setRenderImage(renderImage);
            shape=nullptr;
            return;
        }
        dynamic_cast<Polygon*>(shape)->close();
        mDrawingArea->setEditing(true);
        setRenderImage(shape->drawWithControlPoints());
    }
    else{
        dynamic_cast<Polygon*>(shape)->pushPoint(new QPoint(event->localPos().toPoint()));
        setRenderImage(shape->draw());
        //setBaseImage(getRenderImage());
    }
}

void PolygonTool::finish(){
    if(shape!=nullptr){
        mDrawingArea->setEditing(false);
        setRenderImage(shape->draw());
        setBaseImage(getRenderImage());
        addShape(shape);
        //delete shape;
        shape = nullptr;
    }
    return;
}
