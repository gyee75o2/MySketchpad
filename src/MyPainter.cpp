#include<QtMath>
#include<QImage>
#include<QPainter>
#include"include/Common.h"
void swap(int&, int&);

void MyPainter::drawEllipse(int x, int y, int rx, int ry, int deg){
    qDebug()<<"rx = "<<rx<<", ry="<<ry;

    int xi = 0, yi = ry;
    //区域1决策参数
    int p1i = 4*ry*ry - 4*rx*rx*ry + rx*rx;
    while(ry*ry*xi < rx*rx*yi){
        set4Pix(xi+x, yi+y, x, y, deg);
        if(p1i > 0){
            p1i += 8*ry*ry*xi + 12*ry*ry - 8*yi*rx*rx + 8*rx*rx;
            yi -= 1;
        }
        else{
            p1i += 8*ry*ry*xi + 12*ry*ry;
        }
        xi +=1;
    }

    xi = rx;
    yi = 0;
    //区域2决策参数
    int p2i = 4*rx*rx - 4*ry*ry*rx + ry*ry;
    while(ry*ry*xi > rx*rx*yi){
        set4Pix(xi + x, yi + y, x, y, deg);
        if(p2i > 0){
            p2i += 8*rx*rx*yi + 12*rx*rx - 8*xi*ry*ry + 8*ry*ry;
            xi -= 1;
        }
        else{
            p2i += 8*rx*rx*yi + 12*rx*rx;
        }
        yi+=1;
    }
}

void MyPainter::drawLine(int x1, int y1, int x2, int y2, bool isDash){
    int a=isDash?6:1;   //掩模
    bool steep = qAbs(x1 - x2) < qAbs(y1 - y2);
    if(steep){
        swap(x1, y1);
        swap(x2, y2);
    }
    if(x1 > x2){
        swap(x1, x2);
        swap(y1,y2);
    }
    int dx = x2 - x1, dy = qAbs(y1 - y2);
    int sy = (y1 > y2)? -1: 1;
    int error = - dx / 2;
    int y = y1;
    for(int x = x1; x <= x2; x ++){
        if(steep){
            if((x-x1)%a <= a/2)
                setPix(y,x);
        }
        else{
            if((x-x1)%a <= a/2)
                setPix(x,y);
        }
        error += dy;
        if(error >= 0){
            y += sy;
            error -= dx;
        }
    }
}

void MyPainter::drawCircle(int xc, int yc, int r){
    int x=0, y=r, dx = 3, dy = 5-2*r, d=1-r;
    //set8Pix(x+xc, y+yc,xc, yc);
    while(x<=y){
        set8Pix(x+xc,y+yc,xc,yc);
        if(d<0){
            d+=dx;
            dx+=2;
            dy+=2;
            x++;
        }
        else{
            d+=dy;
            dx+=2;
            dy+=4;
            x++;
            y--;
        }
    }
}

bool MyPainter::setPix(double x, double y){
    if(x<0||x>source->width()-1||y<0||y>source->height()-1)
        return false;
    QPainter painter(source);
    painter.setPen(*pen);
    painter.drawPoint(QPointF(x, y));
    //source->setPixelColor(x,y,color);
    return true;
}

void MyPainter::set4Pix(int x, int y, int xc, int yc, int deg){
    /*
    setPix(x,y);
    setPix(-x+2*xc, y);
    setPix(-x+2*xc, -y+2*yc);
    setPix(x, -y+2*yc);
    */
    setRotatePix(xc, yc, x, y, deg);
    setRotatePix(xc, yc, -x+2*xc, y, deg);
    setRotatePix(xc, yc, -x+2*xc, -y+2*yc, deg);
    setRotatePix(xc, yc, x, -y+2*yc, deg);
}

void MyPainter::set8Pix(int x, int y, int xc, int yc){
    setPix(x,y);
    setPix(x,-y+2*yc);
    setPix(-x+2*xc,y);
    setPix(-x+2*xc,-y+2*yc);
    setPix(y-yc+xc,x-xc+yc);
    setPix(y-yc+xc,-x+xc+yc);
    setPix(-y+yc+xc,x-xc+yc);
    setPix(-y+yc+xc,-x+xc+yc);
}

void MyPainter::setRotatePix(int xc, int yc, int x, int y, int deg){
    qreal dx = x-xc, dy = y-yc;
    qreal rad = (deg/180.0)*M_PI;
    int x_ = int(dx*qCos(rad) - dy*qSin(rad))+xc;
    int y_ = int(dy*qCos(rad) + dx*qSin(rad))+yc;
    setPix(x_,y_);
}

void MyPainter::scanLineFill(const QPoint& p, const QColor& newColor){
    QColor oldColor = source->pixelColor(p);
    if(oldColor == newColor)
        return;

    QStack<QPoint>stack;
    stack.push(p);
    while(!stack.empty()){
        QPoint s = stack.pop();
        int x = s.x(), y = 0;
        while(x>=0 && source->pixelColor(x, s.y())==oldColor){
            source->setPixelColor(x,s.y(),newColor);
            x--;
        }
        int xl = x+1;
        x = s.x()+1;
        while(x<source->width() && source->pixelColor(x, s.y()) == oldColor){
            source->setPixelColor(x, s.y(), newColor);
            x++;
        }
        int xr = x-1;

        x = xl;
        y = s.y()-1;
        while(y>=0&&x<xr){
            bool scanNeedFill = false;
            while(x<xr&&source->pixelColor(x,y)==oldColor){
                scanNeedFill = true;
                x++;
            }
            if(scanNeedFill){
                stack.push(QPoint(x-1, y));
            }
            while(source->pixelColor(x,y)!=oldColor && x < xr)
                x++;
        }

        x=xl;
        y = s.y()+1;
        while(y<source->height()&&x<xr){
            bool scanNeedFill = false;
            while(x<xr&&source->pixelColor(x,y)==oldColor){
                scanNeedFill = true;
                x++;
            }
            if(scanNeedFill){
                stack.push(QPoint(x-1, y));
            }
            while(source->pixelColor(x,y)!=oldColor && x < xr)
                x++;
        }
    }
}

void MyPainter::floodfill(const QPoint& p, const QColor& newColor){
    QPoint *startPoint = new QPoint(p);
    QColor oldColor = source->pixelColor(*startPoint);

    QQueue<QPoint*> queue;
    queue.push_back(startPoint);

    //qDebug()<<source->width()<<source->height();

    while(!queue.empty()){
        QPoint *p = queue.dequeue();
        if(p->x()<0||p->x()>=source->width()||p->y()<0||p->y()>=source->height()){
            delete p;
            continue;
        }
        if(source->pixelColor(*p)==oldColor
                &&source->pixelColor(*p)!=newColor){
            source->setPixelColor(*p,newColor);
            queue.push_back(new QPoint(p->x(), p->y()+1));
            queue.push_back(new QPoint(p->x(), p->y()-1));
            queue.push_back(new QPoint(p->x()+1, p->y()));
            queue.push_back(new QPoint(p->x()-1, p->y()));
        }
        delete p;
    }
}

void MyPainter::drawBezier(QVector<QPoint*> &points, qreal precision){
    double u = 0;
    assert(points.size() >=2);
    QPoint pre(-1,-1);
    while(u < 1){
        QList<QPointF> temp;
        for(int i = 0; i < points.size(); i ++){
            temp.push_back(*points[i]);
        }
        while(temp.size() > 1){
            for(auto it = temp.end() - 1; it > temp.begin(); it --){
                double x = u*(*it).x() + (1-u)*(*(it-1)).x();
                double y = u*(*it).y() + (1-u)*(*(it-1)).y();
                *it = QPointF(x, y);
            }
            temp.pop_front();
        }
        double x = (*temp.begin()).rx(), y = (*temp.begin()).ry();
        if(pre != QPoint(-1, -1)){
            drawLine(int(x),int(y), pre.x(), pre.y());
        }
        pre.setX(int(x));
        pre.setY(int(y));
        //setPix(x,y);
        u+=precision;
    }
    drawLine(pre.x(), pre.y(), points.back()->x(),points.back()->y());
}

inline void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
    return;
}
