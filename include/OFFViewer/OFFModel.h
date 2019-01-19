#ifndef OFFMODEL_H
#define OFFMODEL_H

#include<QString>
#include<qopengl.h>
#include<QVector>
#include<QVector3D>

class OFFModel{
public:
    OFFModel(const QString &filename);
    int count();
    const GLfloat* constData();
    QVector<int> mFaces;

private:
    QVector<GLfloat> mData;
    QVector<QVector3D> mVertices;
    void normalize();
};

#endif // OFFMODEL_H
