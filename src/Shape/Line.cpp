#include"include/Shape/Line.h"
#include"include/Common.h"

Line::Line(DrawingArea *a):Shape(a){
    points.clear();
}

Line::~Line(){
    for(auto it = originPoints.begin(); it<originPoints.end(); it++){
        delete originPoints.back();
    }
    originPoints.clear();
}

void Line::pushPoint(QPoint *point){
    points.push_back(point);
    originPoints.push_back(new QPoint(*point));
    if(points.size()==2)
        center = (*points[0] + *points[1])/2;
}

void Line::popPoint(){
    delete points.back();
    points.pop_back();
    delete originPoints.back();
    originPoints.pop_back();
}

QVector<QPoint*>& Line::getPoints(){
    return points;
}

QImage* Line::draw(){
    QImage *paintingImg = new QImage(*getBaseImage());
    if(points.size() < 2)
        return paintingImg;
    QPen pen(borderColor);
    pen.setWidth(width);
    MyPainter painter(paintingImg, &pen);
    painter.drawLine(points[0]->x(),points[0]->y(), points[1]->x(),points[1]->y());
    //setRenderImage(paintingImg);
    return paintingImg;
}

bool Line::contain(const QPoint &p){
    if(distanceOfPointToLine(p, *points[0], *points[1]) < 10)
        return true;
    return false;
}

void Line::setControlPoint(QVector<QPoint*>::iterator it, const QPoint& p){
    Shape::setControlPoint(it, p);
    for(int i = 0; i < points.size(); i ++){
        *originPoints[i] = rotatePoint(center, *points[i], -deg);
    }
}

void Line::move(const QPoint& p){
    Shape::move(p);
    for(int i = 0; i < points.size() ; i ++){
        *originPoints[i] = rotatePoint(center, *points[i], -deg);
    }
}

void Line::setDeg(int deg){
    Shape::setDeg(deg);
    for(int i = 0; i < points.size(); i ++){
        *points[i] = rotatePoint(center, *originPoints[i], deg);
    }
}

void Line::addScaleFactor(int factor){
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

QImage* Line::dispose(){
    QImage *paintingImg = new QImage(*getBaseImage());
    if(points.size() < 2)
        return paintingImg;
    QPen pen("white");
    pen.setWidth(width);
    MyPainter painter(paintingImg, &pen);
    painter.drawLine(points[0]->x(),points[0]->y(), points[1]->x(),points[1]->y());
    //setRenderImage(paintingImg);
    return paintingImg;
}
