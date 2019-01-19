#include "include/Common.h"
#include "include/Shape/Line.h"

int distanceOf2Points(const QPoint& p1, const QPoint& p2){
    int x1 = p1.x(), x2 = p2.x();
    int y1 = p1.y(), y2 = p2.y();
    int dx = x1-x2, dy = y1-y2;
    return int(sqrt(dx*dx+dy*dy));
}

QPoint rotatePoint(const QPoint &center, const QPoint &p, int deg){
    int xc = center.x(), yc = center.y();
    int x = p.x(), y = p.y();
    qreal dx = x-xc, dy = y-yc;
    qreal rad = (deg/180.0)*M_PI;
    int x_ = int(dx*qCos(rad) - dy*qSin(rad))+xc;
    int y_ = int(dy*qCos(rad) + dx*qSin(rad))+yc;
    return QPoint(x_, y_);
}

int distanceOfPointToLine(const QPoint& p, const QPoint &p1, const QPoint &p2){
    int dx = p1.x()-p2.x(), dy = p1.y()-p2.y();
    qreal d = (qAbs(-(dy)*p.x()+dx*p.y()+((p2.x()*p1.y())-(p1.x()*p2.y()))))/(sqrt(dy*dy+dx*dx));
    return int(d);
}

bool clipLine(Line* line, int xmin, int xmax, int ymin, int ymax){
    QPoint start = *line->points[0], end = *line->points[1];
    int dx = end.x() - start.x(), dy = end.y() - start.y();
    int p[4], q[4];
    p[0] = -dx; q[0] = start.x()-xmin;
    p[1] = dx; q[1] = xmax - start.x();
    p[2] = -dy; q[2] = start.y() - ymin;
    p[3] = dy; q[3] = ymax - start.y();

    double u1=0, u2=1;
    for(int i = 0; i < 4; i ++){
        if(p[i] == 0){
            if(q[i] < 0) return false;
            continue;
        }
        else{
            double rk = double(q[i]) / p[i];
            if(p[i] > 0){   //from inner to outer
                u2 = (rk < u2)?rk:u2;
            }
            else{           //from outer to inner
                u1 = (rk > u1)?rk:u1;
            }
        }
    }
    qDebug()<<u1<<" "<<u2;
    if(u1>=u2)
        return false;
    else{
        *line->points[0] = QPoint(start.x()+int(u1*dx), start.y()+int(u1*dy));
        *line->originPoints[0] = rotatePoint(line->center, *line->points[0], -line->deg);
        *line->points[1] = QPoint(start.x()+int(u2*dx), start.y()+int(u2*dy));
        *line->originPoints[1] = rotatePoint(line->center, *line->points[1], -line->deg);
        return true;
    }
}
