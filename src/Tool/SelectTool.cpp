#include"include/Tool/Selecttool.h"
#include"include/Shape/Line.h"
#include"include/Shape/Circle.h"
#include"include/Shape/Ellipse.h"
#include"include/Shape/Polygon.h"
#include"include/Shape/Curve.h"

SelectTool::SelectTool(DrawingArea *d):Tool(d){
    selectedTool = DrawingArea::NONE;
}

SelectTool::~SelectTool(){

}

void SelectTool::mousePressEvent(QMouseEvent *event){
    if(selectedTool!=DrawingArea::NONE){
        mDrawingArea->mTools[selectedTool]->mousePressEvent(event);
        if(mDrawingArea->mEditing==false){
            delete mDrawingArea->mTools[selectedTool]->getShape();
            mDrawingArea->mTools[selectedTool]->setShape(nullptr);
            selectedTool = DrawingArea::NONE;
        }
    }
}

void SelectTool::mouseMoveEvent(QMouseEvent *event){
    if(selectedTool!=DrawingArea::NONE){
        mDrawingArea->mTools[selectedTool]->mouseMoveEvent(event);
    }
}

void SelectTool::mouseReleaseEvent(QMouseEvent *event){
    if(selectedTool == DrawingArea::NONE){
        Shape *selected = nullptr;
        for(auto it = mDrawingArea->shapes.begin(); it < mDrawingArea->shapes.end(); it++){
            if((*it)->contain(event->localPos().toPoint())){
                selected = *it;
                if(mDrawingArea->mRenderImage!=nullptr)
                    delete mDrawingArea->mRenderImage;
                mDrawingArea->mRenderImage = selected->dispose();
                *(mDrawingArea->mBaseImage) = *(mDrawingArea->mRenderImage);
                continue;
            }
        }
        if(selected != nullptr){
            auto it = mDrawingArea->shapes.begin();
            while(it < mDrawingArea->shapes.end()){
                if(*it == selected){
                    mDrawingArea->shapes.erase(it);
                    continue;
                }
                if(mDrawingArea->mRenderImage != nullptr)
                    delete mDrawingArea->mRenderImage;
                mDrawingArea->mRenderImage = (*it)->draw();
                *(mDrawingArea->mBaseImage) = *(mDrawingArea->mRenderImage);
                it++;
            }
            if(mDrawingArea->mRenderImage != nullptr)
                delete mDrawingArea->mRenderImage;
            mDrawingArea->mRenderImage = selected->drawWithControlPoints();
            mDrawingArea->setEditing(true);
            if(typeid(*selected) == typeid(Line)){
                selectedTool = DrawingArea::LINE;
            }
            else if(typeid(*selected) == typeid(Circle)){
                selectedTool = DrawingArea::CIRCLE;
            }
            else if(typeid(*selected) == typeid(Ellipse)){
                selectedTool = DrawingArea::ELLIPSE;
            }
            else if(typeid(*selected)== typeid(Polygon)){
                selectedTool = DrawingArea::POLYGON;
            }
            else if(typeid(*selected) == typeid(Curve)){
                selectedTool = DrawingArea::CURVE;
            }
            mDrawingArea->mTools[selectedTool]->setShape(selected);
            mDrawingArea->setDeg(selected->getDeg());
            return;
        }
    }
    else{
        mDrawingArea->mTools[selectedTool]->mouseReleaseEvent(event);
    }
}

void SelectTool::finish(){
    if(selectedTool==DrawingArea::NONE){
        return;
    }
    else{
        mDrawingArea->mTools[selectedTool]->finish();
        selectedTool=DrawingArea::NONE;
    }
}
