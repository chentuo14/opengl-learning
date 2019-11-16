#include "nehewidget.h"
#include "ui_nehewidget.h"

NeHeWidget::NeHeWidget(QWidget *parent)
    : QGLWidget (parent)
{
    fullscreen = fs;
    this->setGeometry(0, 0, 640, 480);
    this->setWindowTitle("NeHe's OpenGl framework");
    if(fullscreen)
        showFullScreen();
}

NeHeWidget::NeHeWidget(QWidget *parent, const char *name, bool fs)
    : QGLWidget (parent), name(name)
{
    fullscreen = fs;
}

NeHeWidget::~NeHeWidget()
{
    delete ui;
}

void NeHeWidget::initializeGL()
{
    //阴影平滑
    glShadeModel(GL_SMOOTH);
    //清除屏幕所用颜色，红，绿，蓝
    glClearColor(0.0, 0.0, 0.0, 0.0);
    //设置深度缓存
    glClearDepth(1.0);
    //启用深度测试
    glDepthFunc(GL_LEQUAL);
    //精细透视修正
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void NeHeWidget::paintGL()
{
    //清除屏幕和深度缓存
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //重置当前的模型观察矩阵
    glLoadIdentity();

    glTranslatef( -1.5,  0.0, -6.0 );
    glBegin( GL_TRIANGLES );
    glVertex3f(  0.0,  1.0,  0.0 );
    glVertex3f( -1.0, -1.0,  0.0 );
    glVertex3f(  1.0, -1.0,  0.0 );
    glEnd();

    glTranslatef(  3.0,  0.0,  0.0 );
    glBegin( GL_QUADS );
    glVertex3f( -1.0,  1.0,  0.0 );
    glVertex3f(  1.0,  1.0,  0.0 );
    glVertex3f(  1.0, -1.0,  0.0 );
    glVertex3f( -1.0, -1.0,  0.0 );
    glEnd();

}

void NeHeWidget::resizeGL(int width, int height)
{
    //防止height为0
    if(height == 0)
        height = 1;

    //重置当前的视口
    glViewport(0, 0, (GLint)width, (GLint)height);
    //选择投影矩阵
    glMatrixMode(GL_PROJECTION);
    //重置投影矩阵
    glLoadIdentity();    
    //建立透视投影矩阵
    gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0 );
    //选择模型观察矩阵
    glMatrixMode(GL_MODELVIEW);
    //重置模型观察矩阵
    glLoadIdentity();
}

void NeHeWidget::keyPressEvent(QKeyEvent *e)
{
    switch ( e->key() )
    {
    case Qt::Key_F2:
        fullscreen = !fullscreen;
        if ( fullscreen )
        {
            showFullScreen();
        }
        else
        {
            showNormal();
            setGeometry( 0, 0, 640, 480 );
        }
        updateGL();
        break;
    case Qt::Key_Escape:
        close();
    }
}
