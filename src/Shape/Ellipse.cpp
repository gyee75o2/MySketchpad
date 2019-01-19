#include"include/Shape/Ellipse.h"
#include"include/Common.h"

Ellipse::Ellipse(DrawingArea *a):Shape(a){
    center = QPoint(0,0);
    rx = 0;
    ry = 0;
    deg = 0;
    for(int i = 0; i < 4; i ++)
        points.push_back(new QPoint(0,0));
}

QImage* Ellipse::draw(){
    if(rx==0||ry==0)
        return new QImage(*getBaseImage());
    QImage *paintingImg = new QImage(getBaseImage()->size(), QImage::Format_ARGB32_Premultiplied);
    QPen pen(borderColor);
    pen.setWidth(width);
    MyPainter painter(paintingImg, &pen);

    painter.drawEllipse(center.x(), center.y(), rx, ry, deg);

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

QImage* Ellipse::drawWithControlPoints(){
    QImage* paintingImage = Shape::drawWithControlPoints();

    QPen pen("cornflowerblue");
    MyPainter painter(paintingImage, &pen);
    painter.drawLine(points[0]->x(), points[0]->y(), points[1]->x(), points[1]->y(), true);
    painter.drawLine(points[0]->x(), points[0]->y(), points[2]->x(), points[2]->y(), true);
    painter.drawLine(points[2]->x(), points[2]->y(), points[3]->x(), points[3]->y(), true);
    painter.drawLine(points[1]->x(), points[1]->y(), points[3]->x(), points[3]->y(), true);
    return paintingImage;
}

void Ellipse::setControlPoint(QVector<QPoint*>::iterator it, const QPoint& p){
    for(int i = 0; i < 4; i ++){
        //*points[i]=rotatePoint(center,*points[i],-deg);
        int x = center.x()+((i%2==0)?-rx:rx);
        int y = center.y()+(((i>>1)%2==0)?-ry:ry);
        *points[i]=QPoint(x, y);
    }
    QPoint vector = rotatePoint(center,p,-deg);

    int index = it - points.begin();
    int r_index = index^3;
    **it = vector;
    *points[r_index] = 2*center-vector;
    for(int i = 0; i < 4; i ++){
        if((i^index)==1){
            points[i]->setY(points[index]->y());
            points[i]->setX(points[r_index]->x());
        }
        else if((i^index)==2){
            points[i]->setY(points[r_index]->y());
            points[i]->setX(points[index]->x());
        }
    }
    rx = qAbs((points[index]->x()-points[r_index]->x())/2);
    ry = qAbs((points[index]->y()-points[r_index]->y())/2);
    for(int i = 0; i < 4; i ++){
        *points[i]=rotatePoint(center,*points[i],deg);
    }
}

void Ellipse::setCenter(QPoint c){
    center = c;
    for(int i = 0; i < 4; i ++){
        int x = (i%2 == 1)?c.x()+rx:c.x()-rx;
        int y = ((i>>1)%2 == 1)?c.y()+ry:c.y()-ry;
        points[i]->setX(x);
        points[i]->setY(y);
    }
}

int Ellipse::getDeg(){
    return deg;
}

void Ellipse::setDeg(int d){
    for(int i = 0; i < 4; i ++){
        int op_x=(i&1)?1:-1, op_y=(i&2)?1:-1;
        points[i]->setX(center.x()+op_x*rx);
        points[i]->setY(center.y()+op_y*ry);
        *points[i] = rotatePoint(center, *points[i], d);
    }
    deg=d;
}

void Ellipse::setParameter(int rx, int ry){
    this->rx = rx;
    this->ry = ry;
    for(int i = 0; i < 4; i ++){
        int x = (i%2 == 1)?center.x()+rx:center.x()-rx;
        int y = ((i>>1)%2 == 1)?center.y()+ry:center.y()-ry;
        points[i]->setX(x);
        points[i]->setY(y);
    }
}

bool Ellipse::contain(const QPoint& p){
    QPoint temp = rotatePoint(center, p, -deg);

    int x = temp.x(), y = temp.y();
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

void Ellipse::move(const QPoint& p){
    //Shape::move(p);
    for(auto it = points.begin(); it < points.end(); it++){
        **it+=p;
    }
    center+=p;
}

void Ellipse::addScaleFactor(int factor){
    if(rx==0&&ry==0){
        return;
    }
    int tempx=int(rx+double(rx)/(rx+ry)*20*factor);
    int tempy=int(ry+double(ry)/(rx+ry)*20*factor);
    if(tempx<0||tempy<0)
        return;
    setParameter(tempx, tempy);
    setDeg(deg);
    return;
}

QImage* Ellipse::dispose(){

    if(rx==0||ry==0)
        return new QImage(*getBaseImage());
    QImage *paintingImg = new QImage(getBaseImage()->size(), QImage::Format_ARGB32_Premultiplied);
    QPen pen("white");
    pen.setWidth(width);
    MyPainter painter(paintingImg, &pen);

    painter.drawEllipse(center.x(), center.y(), rx, ry, deg);
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
