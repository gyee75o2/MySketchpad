#include"include/Shape/Polygon.h"
#include"include/Common.h"

Polygon::Polygon(DrawingArea *a):Shape(a){
    isClosed = false;
}

Polygon::~Polygon(){
    for(auto it = points.begin(); it!=points.end();it++){
        delete *it;
    }
    points.clear();
}

void Polygon::close(){
    isClosed = true;
    QPoint sum(0,0);
    for(auto it = points.begin(); it != points.end(); it ++){
        sum+=**it;
    }
    center = sum/points.size();
}

QVector<QPoint*>& Polygon::getPoints(){
    return points;
}

QImage* Polygon::draw(){
    QImage *paintingImage = new QImage(*getBaseImage());
    if(fillColor!="white"&&isClosed){
        QPainter p(paintingImage);
        QBrush brush(fillColor);
        p.setBrush(brush);
        QPoint* ps = new QPoint[points.size()];
        for(int i = 0; i < points.size(); i ++){
            ps[i] = *points[i];
        }
        p.drawPolygon(ps,points.size());
        delete[] ps;
    }
    //QImage *paintingImage = scanFill();
    QPen pen(borderColor);
    pen.setWidth(width);
    MyPainter painter(paintingImage, &pen);
    for(auto it = points.begin(); it!=points.end()-1; it++){
        painter.drawLine((*it)->x(), (*it)->y(), (*(it+1))->x(), (*(it+1))->y());
    }
    if(isClosed){
        painter.drawLine((*points.begin())->x(), (*points.begin())->y(), (*(points.end()-1))->x(), (*(points.end()-1))->y());
    }
    return paintingImage;
}

void Polygon::pushPoint(QPoint *point){
    points.push_back(point);
    originPoints.push_back(new QPoint(*point));
}

void Polygon::popPoint(){
    delete points.back();
    points.pop_back();
    delete originPoints.back();
    originPoints.pop_back();
}

bool Polygon::contain(const QPoint& p){
    for(int i = 0; i < points.size(); i ++){
        if(distanceOfPointToLine(p, *points[i], *points[(i+1)%points.size()]) < 10)
            return true;
    }
    return false;
}


void Polygon::setControlPoint(QVector<QPoint*>::iterator it, const QPoint& p){
    Shape::setControlPoint(it, p);
    for(int i = 0; i < points.size(); i ++){
        *originPoints[i] = rotatePoint(center, *points[i], -deg);
    }
}

void Polygon::move(const QPoint& p){
    Shape::move(p);
    for(int i = 0; i < points.size() ; i ++){
        *originPoints[i] = rotatePoint(center, *points[i], -deg);
    }
}

void Polygon::setDeg(int deg){
    Shape::setDeg(deg);
    for(int i = 0; i < points.size(); i ++){
        *points[i] = rotatePoint(center, *originPoints[i], deg);
    }
}

void Polygon::addScaleFactor(int factor){
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

QImage* Polygon::dispose(){
    QImage *paintingImage = new QImage(*getBaseImage());
    if(fillColor!="white"&&isClosed){
        QPainter p(paintingImage);
        QBrush brush("white");
        p.setBrush(brush);
        QPoint* ps = new QPoint[points.size()];
        for(int i = 0; i < points.size(); i ++){
            ps[i] = *points[i];
        }
        p.drawPolygon(ps,points.size());
        delete[] ps;
    }
    //QImage *paintingImage = scanFill();
    QPen pen("white");
    pen.setWidth(width);
    MyPainter painter(paintingImage, &pen);
    for(auto it = points.begin(); it!=points.end()-1; it++){
        painter.drawLine((*it)->x(), (*it)->y(), (*(it+1))->x(), (*(it+1))->y());
    }
    if(isClosed){
        painter.drawLine((*points.begin())->x(), (*points.begin())->y(), (*(points.end()-1))->x(), (*(points.end()-1))->y());
    }
    return paintingImage;
}
