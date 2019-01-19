#include"include/Shape/Circle.h"
#include"include/Common.h"

Circle::Circle(DrawingArea *a):Shape(a){
    center = QPoint(0,0);
    radius = 0;
    for(int i = 0; i < 4; i ++)
        points.push_back(new QPoint(0,0));
}

Circle::~Circle(){
    for(auto it = points.begin(); it!=points.end(); it++){
        delete *it;
    }
    points.clear();
}

void Circle::setCenter(QPoint c){
    this->center = c;
    for(int i = 0; i < 4; i ++){
        int x = (i%2 == 1)?c.x()+radius:c.x()-radius;
        int y = ((i>>1)%2 == 1)?c.y()+radius:c.y()-radius;
        points[i]->setX(x);
        points[i]->setY(y);
    }
}

void Circle::setRadius(int r){
    radius = r;
    for(int i = 0; i < 4; i ++){
        int x = (i%2 == 1)?center.x()+radius:center.x()-radius;
        int y = ((i>>1)%2 == 1)?center.y()+radius:center.y()-radius;
        points[i]->setX(x);
        points[i]->setY(y);
    }
}

QImage* Circle::draw(){
    if(radius==0)
        return new QImage(*getBaseImage());
    QImage *paintingImg = new QImage(getBaseImage()->size(), QImage::Format_ARGB32_Premultiplied);

    QPen pen(borderColor);
    pen.setWidth(width);
    MyPainter painter(paintingImg, &pen);

    painter.drawCircle(center.x(), center.y(),radius);
    if(fillColor!="white"){
        QPoint temp = center;
        if(center.x()<0)
            temp.setX(0);
        if(center.x()>=getBaseImage()->width())
            temp.setX(getBaseImage()->width()-1);
        if(center.y()<0)
            temp.setY(0);
        if(center.y()>=getBaseImage()->height())
            temp.setY(getBaseImage()->height()-1);

        painter.scanLineFill(temp, fillColor);
    }

    QPainter qpainter(paintingImg);
    qpainter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    qpainter.drawImage(0, 0, *getBaseImage());

    return paintingImg;
}

QPoint Circle::getCenter(){
    return center;
}

int Circle::getRadius(){
    return radius;
}

QImage* Circle::drawWithControlPoints(){
    QImage* paintingImage=Shape::drawWithControlPoints();
    QPen pen("cornflowerblue");
    MyPainter painter(paintingImage, &pen);
    painter.drawLine(points[0]->x(), points[0]->y(), points[1]->x(), points[1]->y(), true);
    painter.drawLine(points[0]->x(), points[0]->y(), points[2]->x(), points[2]->y(), true);
    painter.drawLine(points[2]->x(), points[2]->y(), points[3]->x(), points[3]->y(), true);
    painter.drawLine(points[1]->x(), points[1]->y(), points[3]->x(), points[3]->y(), true);
    return paintingImage;
}

void Circle::setControlPoint(QVector<QPoint*>::iterator it, const QPoint& p){
    int index = it-points.begin();
    QPoint vector = p-**it;
    int opx=(index%2)?1:-1, opy=((index>>1)%2)?1:-1;
    if(opx*vector.x() > opy*vector.y())
        vector.setY(opx*opy*vector.x());
    else
        vector.setX(opx*opy*vector.y());
    **it+=vector;
    for(int i = 0; i < 4; i ++){
        if((i^index)==1)
            points[i]->setY((*it)->y());
        else if((i^index)==2)
            points[i]->setX((*it)->x());
    }
    center = (*points[3] + *points[0])/2;
    radius = qAbs((points[3]->x() - points[0]->x())/2);
}

bool Circle::contain(const QPoint &p){
    int x = p.x(), y = p.y();
    int xmin=100000, xmax=-100000, ymin=100000, ymax=-100000;
    for(int i = 0; i < 4; i ++){
        xmin = points[i]->x()<xmin?points[i]->x():xmin;
        xmax = points[i]->x()>xmax?points[i]->x():xmax;
        ymin = points[i]->y()<ymin?points[i]->y():ymin;
        ymax = points[i]->y()>ymax?points[i]->y():ymax;
    }
    if(x>xmin && x < xmax
            &&y>ymin && y<ymax){
        return true;
    }
    return false;
}

void Circle::move(const QPoint &p){
    //Shape::move(p);
    for(auto it = points.begin(); it<points.end(); it++){
        **it+=p;
    }
    center+=p;
}

void Circle::addScaleFactor(int factor){
    int temp = (radius+10*factor > 0)?radius+10*factor:0;
    setRadius(temp);
}

QImage* Circle::dispose(){
    if(radius==0)
        return new QImage(*getBaseImage());
    QImage *paintingImg = new QImage(getBaseImage()->size(), QImage::Format_ARGB32_Premultiplied);

    QPen pen("white");
    pen.setWidth(width);
    MyPainter painter(paintingImg, &pen);

    painter.drawCircle(center.x(), center.y(),radius);
    if(fillColor!="white"){
        QPoint temp = center;
        if(center.x()<0)
            temp.setX(0);
        if(center.x()>=getBaseImage()->width())
            temp.setX(getBaseImage()->width()-1);
        if(center.y()<0)
            temp.setY(0);
        if(center.y()>=getBaseImage()->height())
            temp.setY(getBaseImage()->height()-1);

        painter.scanLineFill(temp, "white");
    }

    QPainter qpainter(paintingImg);
    qpainter.setCompositionMode(QPainter::CompositionMode_DestinationOver);
    qpainter.drawImage(0, 0, *getBaseImage());

    return paintingImg;
}
