#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include "include/OFFViewer/OFFModel.h"

QT_FORWARD_DECLARE_CLASS(QOpenGLShaderProgram)

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0, OFFModel* model = 0);
    ~GLWidget();

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void cleanup();

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    void setupVertexAttribs();

    float mScale;
    int mXRot;
    int mYRot;
    int mZRot;
    QPoint mLastPos;
    OFFModel* mModel;
    QOpenGLVertexArrayObject mVao;
    QOpenGLBuffer mModelVbo;
    QOpenGLShaderProgram *mProgram;
    int mProjMatrixLoc;
    int mMvMatrixLoc;
    int mNormalMatrixLoc;
    int mLightPosLoc;
    QMatrix4x4 mProj;
    QMatrix4x4 mCamera;
    QMatrix4x4 mWorld;
};

#endif // GLWIDGET_H
