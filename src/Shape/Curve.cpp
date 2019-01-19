#include "include/Shape/Curve.h"
#include "include/Common.h"

Curve::Curve(DrawingArea *d):Shape(d){
    finished = false;
}

Curve::~Curve(){
    for(auto it = originPoints.begin(); it < originPoints.end(); it++){
        delete *it;
    }
    originPoints.clear();
}
/*
QVector<QPoint*>& Curve::getPoints(){
    return points;
}
*/

QImage* Curve::draw(){
    QImage *paintingImage = new QImage(*getBaseImage());
    //QImage *paintingImage = scanFill();
    QPen pen("cornflowerblue");
    pen.setWidth(1);
    MyPainter painter(paintingImage, &pen);
    if(!finished){
        for(auto it = points.begin(); it!=points.end()-1; it++){
            painter.drawLine((*it)->x(), (*it)->y(), (*(it+1))->x(), (*(it+1))->y(), true);
        }
    }
    pen.setColor(borderColor);
    pen.setWidth(width);
    painter.drawBezier(points, 0.01);
    return paintingImage;
}

QImage* Curve::drawWithControlPoints(){
    QImage *paintingImage = Shape::drawWithControlPoints();
    QPen pen("cornflowerblue");
    pen.setWidth(1);
    MyPainter painter(paintingImage, &pen);
    for(auto it = points.begin(); it < points.end() - 1; it ++){
        painter.drawLine((*it)->x(), (*it)->y(), (*(it+1))->x(), (*(it+1))->y(), true);
    }
    return paintingImage;
}

void Curve::pushPoint(const QPoint &point){
    points.push_back(new QPoint(point));
    originPoints.push_back(new QPoint(point));
}

void Curve::popPoint(){
    delete points.back();
    points.pop_back();
    delete originPoints.back();
    originPoints.pop_back();
}

bool Curve::contain(const QPoint& p){
    for(int i = 0; i < points.size() - 1; i ++){
        if(distanceOfPointToLine(p, *points[i], *points[i+1]) < 10)
            return true;
    }
    return false;
}

void Curve::setControlPoint(QVector<QPoint*>::iterator it, const QPoint& p){
    Shape::setControlPoint(it, p);
    for(int i = 0; i < points.size(); i ++){
        *originPoints[i] = rotatePoint(center, *points[i], -deg);
    }
}

void Curve::move(const QPoint& p){
    Shape::move(p);
    for(int i = 0; i < points.size() ; i ++){
        *originPoints[i] = rotatePoint(center, *points[i], -deg);
    }
}

void Curve::setDeg(int deg){
    Shape::setDeg(deg);
    for(int i = 0; i < points.size(); i ++){
        *points[i] = rotatePoint(center, *originPoints[i], deg);
    }
}

void Curve::addScaleFactor(int factor){
    double ratio = double(100+10*(factor))/100;
    QPoint sum;
    for(int i = 0; i < originPoints.size(); i ++){
        *originPoints[i] = ratio*(*originPoints[i]-center)+center;
        sum+=*originPoints[i];
    }
    center = sum/originPoints.size();
    setDeg(deg);
    return;
}

QImage* Curve::dispose(){
    QImage *paintingImage = new QImage(*getBaseImage());
    //QImage *paintingImage = scanFill();
    QPen pen("white");
    pen.setWidth(width);
    MyPainter painter(paintingImage, &pen);
    painter.drawBezier(points, 0.01);
    return paintingImage;
}

