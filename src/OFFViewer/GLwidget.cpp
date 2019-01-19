#include "include/OFFViewer/GLWidget.h"
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include <QCoreApplication>
#include <math.h>

GLWidget::GLWidget(QWidget *parent, OFFModel *model)
: QOpenGLWidget(parent),
  mScale(0.5),
  mXRot(315*8),
  mYRot(315*8),
  mZRot(0),
  mModel(model),
  mProgram(nullptr){

}

GLWidget::~GLWidget(){
    cleanup();
}

int normalizeAngle(int angle){
    while(angle <= 0){
        angle += 16*360;
    }
    while(angle > 16*360){
        angle -= 16*160;
    }
    return angle;
}

void GLWidget::setXRotation(int angle){
    normalizeAngle(angle);
    if (angle != mXRot) {
        mXRot = angle;
        emit xRotationChanged(angle);
        update();
    }
}

void GLWidget::setYRotation(int angle){
    normalizeAngle(angle);
    if (angle != mYRot) {
        mYRot = angle;
        emit yRotationChanged(angle);
        update();
    }
}

void GLWidget::setZRotation(int angle){
    normalizeAngle(angle);
    if (angle != mZRot) {
        mZRot = angle;
        emit zRotationChanged(angle);
        update();
    }
}

void GLWidget::cleanup(){
    if (mProgram == nullptr)
        return;
    makeCurrent();
    mModelVbo.destroy();
    delete mProgram;
    mProgram = nullptr;
    delete mModel;
    doneCurrent();
}

static const char *vertexShaderSource =
    "#version 330\n"
    "in vec4 vertex;\n"
    "in vec3 normal;\n"
    "out vec3 vert;\n"
    "out vec3 vertNormal;\n"
    "uniform mat4 projMatrix;\n"
    "uniform mat4 mvMatrix;\n"
    "uniform mat3 normalMatrix;\n"
    "void main() {\n"
    "   vert = vertex.xyz;\n"
    "   vertNormal = normalMatrix * normal;\n"
    "   gl_Position = projMatrix * mvMatrix * vertex;\n"
    "}\n";



static const char *fragmentShaderSource =
    "#version 330\n"
    "in highp vec3 vert;\n"
    "in highp vec3 vertNormal;\n"
    "out highp vec4 fragColor;\n"
    "uniform highp vec3 lightPos;\n"
    "void main() {\n"
    "   highp vec3 L = normalize(lightPos - vert);\n"
    "   highp float NL = max(dot(normalize(vertNormal), L), 0.0);\n"
    "   highp vec3 color = vec3(0.39, 1.0, 0.0);\n"
    "   highp vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
    "   fragColor = vec4(col, 1.0);\n"
    "}\n";


void GLWidget::initializeGL()
{
    // In this example the widget's corresponding top-level window can change
    // several times during the widget's lifetime. Whenever this happens, the
    // QOpenGLWidget's associated context is destroyed and a new one is created.
    // Therefore we have to be prepared to clean up the resources on the
    // aboutToBeDestroyed() signal, instead of the destructor. The emission of
    // the signal will be followed by an invocation of initializeGL() where we
    // can recreate all resources.
    connect(context(), &QOpenGLContext::aboutToBeDestroyed, this, &GLWidget::cleanup);

    initializeOpenGLFunctions();
    glClearColor(0, 0, 0, 1);

    mProgram = new QOpenGLShaderProgram;
    mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    mProgram->bindAttributeLocation("vertex", 0);
    mProgram->bindAttributeLocation("normal", 1);
    mProgram->link();

    mProgram->bind();
    mProjMatrixLoc = mProgram->uniformLocation("projMatrix");
    mMvMatrixLoc = mProgram->uniformLocation("mvMatrix");
    mNormalMatrixLoc = mProgram->uniformLocation("normalMatrix");
    mLightPosLoc = mProgram->uniformLocation("lightPos");

    // Create a vertex array object. In OpenGL ES 2.0 and OpenGL 2.x
    // implementations this is optional and support may not be present
    // at all. Nonetheless the below code works in all cases and makes
    // sure there is a VAO when one is needed.
    mVao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&mVao);

    // Setup our vertex buffer object.
    mModelVbo.create();
    mModelVbo.bind();
    mModelVbo.allocate(mModel->constData(), mModel->count() * sizeof(GLfloat));

    // Store the vertex attribute bindings for the program.
    setupVertexAttribs();

    // Our camera never changes in this example.
    mCamera.setToIdentity();
    mCamera.translate(0, 0, -1);

    // Light position is fixed.
    mProgram->setUniformValue(mLightPosLoc, QVector3D(0, 0, 70));

    mProgram->release();
}

void GLWidget::setupVertexAttribs()
{
    mModelVbo.bind();
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    mModelVbo.release();
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    mWorld.setToIdentity();

    mWorld.scale(QVector3D(mScale, mScale, mScale));
    mWorld.rotate(180.0f - (mXRot / 16.0f), 1, 0, 0);
    mWorld.rotate(mYRot / 16.0f, 0, 1, 0);
    mWorld.rotate(mZRot / 16.0f, 0, 0, 1);

    QOpenGLVertexArrayObject::Binder vaoBinder(&mVao);
    mProgram->bind();
    mProgram->setUniformValue(mProjMatrixLoc, mProj);
    mProgram->setUniformValue(mMvMatrixLoc, mCamera * mWorld);
    QMatrix3x3 normalMatrix = mWorld.normalMatrix();
    mProgram->setUniformValue(mNormalMatrixLoc, normalMatrix);

    int p = 0;


    for(int i = 0; i < mModel->mFaces.size(); i ++){
        glDrawArrays(GL_TRIANGLE_FAN, p, mModel->mFaces[i]);
        p+=mModel->mFaces[i];
    }

    mProgram->release();
}

void GLWidget::resizeGL(int w, int h)
{
    mProj.setToIdentity();
    mProj.perspective(45.0f, GLfloat(w) / h, 0.01f, 100.0f);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    mLastPos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - mLastPos.x();
    int dy = event->y() - mLastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(mXRot + 8 * dy);
        setYRotation(mYRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(mXRot + 8 * dy);
        setZRotation(mZRot + 8 * dx);
    }
    mLastPos = event->pos();
}

void GLWidget::wheelEvent(QWheelEvent* event){
    mScale += 0.01*event->delta()/120;
    if(mScale < 0)
        mScale = 0;
    update();
}
