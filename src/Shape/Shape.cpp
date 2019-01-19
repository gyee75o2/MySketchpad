#include"include/Shape/Shape.h"
#include"include/Common.h"

Shape::~Shape(){
    for(auto it = points.begin(); it!=points.end(); it++){
        delete *it;
    }
    points.clear();
}

Shape::Shape(DrawingArea* a){
    mDrawingArea = a;
    fillColor = a->fillColor();
    borderColor=a->penColor();
    width=a->penThickness()+1;
    deg=0;
}

QImage* Shape::getBaseImage(){
    return mDrawingArea->mBaseImage;
}

QPen* Shape::getPen(){
    return mDrawingArea->mPen;
}

QImage* Shape::drawWithControlPoints(){
    QImage *paintingImage = draw();
    QPen *pen = new QPen("black");
    MyPainter painter(paintingImage, pen);
    auto it = points.begin();
    for(; it != points.end(); it++){
        //QRect rect((*it)->x()-3, (*it)->y()-3, 7, 7);
        painter.drawCircle((*it)->x(), (*it)->y(), 5);
        //painter.fillRect(rect.x()+1,rect.y()+1, rect.width()-1, rect.height()-1,"white");
    }
    delete pen;
    return paintingImage;
}

void Shape::setControlPoint(QVector<QPoint*>::iterator it, const QPoint& p){
    **it = p;
    QPoint sum(0,0);
    for(auto it = points.begin(); it != points.end(); it ++){
        sum+=**it;
    }
    center = sum/points.size();
}

bool Shape::grabControlPoint(QVector<QPoint*>::iterator &it, const QPoint& p){
    for(it = points.begin();it!= points.end(); it ++){
        if((*(*it) - p).manhattanLength()<10){
            return true;
        }
    }
    return false;
}

void Shape::setDeg(int deg){
    this->deg = deg;
    return;
}

bool Shape::contain(const QPoint &p){
    UNUSED(p);
    return false;
}

void Shape::move(const QPoint& p){
    QPoint sum(0,0);
    for(auto it = points.begin(); it != points.end(); it ++){
        *(*it) += p;
        sum+=**it;
    }
    center = sum/points.size();
    return;
}

void Shape::addScaleFactor(int factor){
    factor+=factor;
}

void Shape::setFillColor(const QColor &color){
    fillColor =  color;
}

void Shape::setBorderColor(const QColor &color){
    borderColor = color;
}

void Shape::setWidth(int width){
    this->width = width;
}

