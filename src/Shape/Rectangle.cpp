#include"include/Shape/Rectangle.h"
#include"include/Common.h"

Rectangle::Rectangle(DrawingArea *d):Shape(d){
    for(int i = 0; i < 4; i ++){
        points.push_back(new QPoint());
    }
}

Rectangle::~Rectangle(){}

void Rectangle::setRect(const QPoint &p1, const QPoint &p2){
    int xmin,xmax,ymin,ymax;
    if(p1.x()<p2.x()){
        xmin = p1.x();
        xmax = p2.x();
    }
    else{
        xmax = p1.x();
        xmin = p2.x();
    }
    if(p1.y()<p2.y()){
        ymin = p1.y();
        ymax = p2.y();
    }
    else{
        ymin = p2.y();
        ymax = p1.y();
    }
    *points[0] = QPoint(xmin,ymin);
    *points[1] = QPoint(xmax,ymin);
    *points[2] = QPoint(xmin,ymax);
    *points[3] = QPoint(xmax,ymax);
}

QImage* Rectangle::draw(){
    QPen pen("cornflowerblue");
    QImage *paintingImg = new QImage(*getBaseImage());
    MyPainter painter(paintingImg, &pen);
    painter.drawLine(points[0]->x(), points[0]->y(), points[1]->x(), points[1]->y(), true);
    painter.drawLine(points[0]->x(), points[0]->y(), points[2]->x(), points[2]->y(), true);
    painter.drawLine(points[2]->x(), points[2]->y(), points[3]->x(), points[3]->y(), true);
    painter.drawLine(points[1]->x(), points[1]->y(), points[3]->x(), points[3]->y(), true);
    return paintingImg;
}

void Rectangle::setControlPoint(QVector<QPoint*>::iterator it, const QPoint& p){
    int index = it-points.begin();
    **it = p;
    for(int i = 0; i < 4; i ++){
        if((i^index)==1){
            points[i]->setY(p.y());
        }
        else if((i^index)==2){
            points[i]->setX(p.x());
        }
    }
}


bool Rectangle::contain(const QPoint &p){
    int x = p.x(), y = p.y();
    if(x>points[0]->x() && x < points[3]->x()
            &&y>points[0]->y() && y<points[3]->y()){
        return true;
    }
    return false;
}
