#ifndef MYPAINTER_H
#define MYPAINTER_H

#include<QImage>

class MyPainter
{
public:
    MyPainter():source(nullptr){}
    MyPainter(QImage *source, QPen *pen):source(source), pen(pen){}

public:
    void drawLine(int x1, int y1, int x2, int y2, bool isDash=false);
    void drawCircle(int x, int y, int r);
    void drawEllipse(int x, int y, int rx, int ry, int deg =0);
    void drawBezier(QVector<QPoint*> &points, qreal precision);
    void floodfill(const QPoint&, const QColor&);
    void scanLineFill(const QPoint&, const QColor&);
    void setImage(QImage *source){this->source = source;}
    bool setPix(double x, double y);
    void set8Pix(int x, int y, int xc, int yc);
    void set4Pix(int x, int y, int xc, int yc, int deg=0);
    void setRotatePix(int xc, int yc, int x, int y, int deg=0);

private:
    QImage *source;
    QPen *pen;
};

#endif // MYPAINTER_H
