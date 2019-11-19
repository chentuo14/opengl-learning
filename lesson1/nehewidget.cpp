#include "nehewidget.h"
#include "ui_nehewidget.h"
#include <QtDebug>
#include <QTimer>

NeHeWidget::NeHeWidget(QWidget *parent)
    : QGLWidget (parent)
{
    fullscreen = fs;
    this->setGeometry(20, 100, 640, 480);
    this->setWindowTitle("NeHe's OpenGl framework");
    if(fullscreen)
        showFullScreen();
}

NeHeWidget::NeHeWidget(QWidget *parent, const char *name, bool fs)
    : QGLWidget (parent), name(name)
{
    rTri = 0.0;
    rQuad = 0.0;
    fullscreen = fs;
    this->setGeometry(20, 20, 640, 480);
    this->setWindowTitle("NeHe's OpenGl framework");
    if(fullscreen)
        showFullScreen();
}

NeHeWidget::~NeHeWidget()
{
    delete ui;
}

void NeHeWidget::initializeGL()
{
    //载入纹理。
    loadGLTextures();

    //启用纹理。如果没有启用的话，你的对象看起来永远都是纯白色，这一定不是什么好事。
    glEnable( GL_TEXTURE_2D );

    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0, 0.0, 0.0, 0.5 );
    glClearDepth( 1.0 );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void NeHeWidget::paintGL()
{
    //清除屏幕和深度缓存
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //重置当前的模型观察矩阵
    glLoadIdentity();

    glTranslated(0.0, 0.0, -5.0);
    //根据xRot、yRot、zRot的实际值来旋转正方体。
    glRotatef( xRot,  1.0,  0.0,  0.0 );
    glRotatef( yRot,  0.0,  1.0,  0.0 );
    glRotatef( zRot,  0.0,  0.0,  1.0 );

    //选择我们使用的纹理。
    glBindTexture( GL_TEXTURE_2D, texture[0] );
    glBegin( GL_QUADS );
    //前面。
    glTexCoord2f( 0.0, 0.0 ); glVertex3f( -1.0, -1.0,  1.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f(  1.0, -1.0,  1.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f(  1.0,  1.0,  1.0 );
    glTexCoord2f( 0.0, 1.0 ); glVertex3f( -1.0,  1.0,  1.0 );

    //后面。
    glTexCoord2f( 1.0, 0.0 ); glVertex3f( -1.0, -1.0, -1.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f( -1.0,  1.0, -1.0 );
    glTexCoord2f( 0.0, 1.0 ); glVertex3f(  1.0,  1.0, -1.0 );
    glTexCoord2f( 0.0, 0.0 ); glVertex3f(  1.0, -1.0, -1.0 );

    //顶面。
    glTexCoord2f( 0.0, 1.0 ); glVertex3f( -1.0,  1.0, -1.0 );
    glTexCoord2f( 0.0, 0.0 ); glVertex3f( -1.0,  1.0,  1.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f(  1.0,  1.0,  1.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f(  1.0,  1.0, -1.0 );

    //底面。
    glTexCoord2f( 1.0, 1.0 ); glVertex3f( -1.0, -1.0, -1.0 );
    glTexCoord2f( 0.0, 1.0 ); glVertex3f(  1.0, -1.0, -1.0 );
    glTexCoord2f( 0.0, 0.0 ); glVertex3f(  1.0, -1.0,  1.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f( -1.0, -1.0,  1.0 );

    //右面。
    glTexCoord2f( 1.0, 0.0 ); glVertex3f(  1.0, -1.0, -1.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f(  1.0,  1.0, -1.0 );
    glTexCoord2f( 0.0, 1.0 ); glVertex3f(  1.0,  1.0,  1.0 );
    glTexCoord2f( 0.0, 0.0 ); glVertex3f(  1.0, -1.0,  1.0 );

    //左面。
    glTexCoord2f( 0.0, 0.0 ); glVertex3f( -1.0, -1.0, -1.0 );
    glTexCoord2f( 1.0, 0.0 ); glVertex3f( -1.0, -1.0,  1.0 );
    glTexCoord2f( 1.0, 1.0 ); glVertex3f( -1.0,  1.0,  1.0 );
    glTexCoord2f( 0.0, 1.0 ); glVertex3f( -1.0,  1.0, -1.0 );


    glEnd();

    xRot += 0.3;
    yRot += 0.2;
    zRot += 0.4;

    QTimer::singleShot(100, this, [=](){
        updateGL();
    });
    qDebug()<<"paintGL end";
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
    switch (e->key()) {
    case Qt::Key_F2:
        fullscreen = !fullscreen;
        if ( fullscreen ) {
            showFullScreen();
        } else {
            showNormal();
            setGeometry( 0, 0, 640, 480 );
        }
        updateGL();
        break;
    case Qt::Key_Escape:
        close();
    }
}

void NeHeWidget::loadGLTextures()
{
    QImage tex, buf;
    if(!buf.load("C:\\Users\\ch122\\Downloads\\rect.jpg")) {
        qWarning("Could not read image file, using signle-color instead.");
        QImage dummy(QSize(128, 128), QImage::Format_RGB32);
        dummy.fill(Qt::green);
        buf = dummy;
    }
    //转换图片
    tex = QGLWidget::convertToGLFormat(buf);
    //创建一个纹理
    glGenTextures( 1, &texture[0] );
    //使用来自位图数据生成的典型纹理
    glBindTexture( GL_TEXTURE_2D, texture[0] );
    //这里真正的创建纹理
    glTexImage2D( GL_TEXTURE_2D, 0, 3, tex.width(), tex.height(), 0,
          GL_RGBA, GL_UNSIGNED_BYTE, tex.bits() );
    //OpenGL采用的滤波方式
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
}
