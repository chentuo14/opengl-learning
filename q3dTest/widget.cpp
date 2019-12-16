#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QGLWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    xRot = 0;
    yRot = 0;
    zRot = 0;
    _far = 0;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::GLGrid(QVector3D &pt1, QVector3D &pt2, int num)
{
    const float _xLen = (pt2.x() - pt1.x()) / num;
    const float _yLen = (pt2.y() - pt1.y()) / num;
    const float _zLen = (pt2.z() - pt1.z()) / num;
    int xi = 0;
    int yi = 0;
    int zi = 0;

    glLineWidth(1.0f);
    glLineStipple(1, 0x0303);//线条样式
    glBegin(GL_LINES);
    glEnable(GL_LINE_SMOOTH);

    //绘制平行于X的直线
    for (zi = 0; zi <= num; zi++)
    {
        float z = _zLen * zi + pt1.z();
        for (yi = 0; yi <= num; yi++) {
            float y = _yLen * yi +pt1.y();
            glVertex3f(pt1.x(), y, z);
            glVertex3f(pt2.x(), y, z);
        }
    }

    //绘制平行于Y的直线
    for (zi = 0; zi <= num; zi++) {
        float z = _zLen * zi + pt1.z();
        for (xi = 0; xi <= num; xi++) {
            float x = _xLen * xi +pt1.x();
            glVertex3f(x, pt1.y(), z);
            glVertex3f(x, pt2.y(), z);
        }
    }
    //绘制平行于Z的直线
    for (yi = 0; yi <= num; yi++) {
        float y = _yLen * yi + pt1.y();
        for (xi = 0; xi <= num; xi++) {
            float x = _xLen * xi +pt1.x();
            glVertex3f(x, y, pt1.z());
            glVertex3f(x, y, pt2.z());
        }
    }
    glEnd();

}

void Widget::GLDrawSpaceAxes()
{
    GLUquadricObj *objCylinder =gluNewQuadric();
    glPushMatrix();
    glColor3f(1.0f,1.0f, 1.0f);
    //    glutSolidSphere(0.25,6,6);
    glColor3f(0.0f,0.0f, 1.0f);
    //    gluCylinder(objCylinder,0.1, 0.1, AXES_LEN, 10, 5);         //Z
    //    glTranslatef(0,0,AXES_LEN);
    gluCylinder(objCylinder,0.3, 0.0, 0.6, 10, 5);                 //Z
    glPopMatrix();
    glPushMatrix();
    //    glTranslatef(0,0.5,AXES_LEN);
    // Print GL Text ToThe Screen
    glRotatef(90,0.0,1.0,0.0);
    //    GLPrint("Z");
    glPopMatrix();
    glPushMatrix();
    glColor3f(0.0f,1.0f, 0.0f);
    glRotatef(-90,1.0,0.0,0.0);
    //    gluCylinder(objCylinder,0.1, 0.1, AXES_LEN, 10, 5);         //Y

    //    glTranslatef(0,0,AXES_LEN);

    gluCylinder(objCylinder,0.3, 0.0, 0.6, 10, 5);                 //Y
    glPopMatrix();
    glPushMatrix();
    //    glTranslatef(0.5,AXES_LEN,0);
    //    GLPrint("Y");                                               // Print GL Text ToThe Screen
    glPopMatrix();
    glPushMatrix();
    glColor3f(1.0f,0.0f, 0.0f);
    glRotatef(90,0.0,1.0,0.0);
    //    gluCylinder(objCylinder,0.1, 0.1, AXES_LEN, 10, 5);         //X
    //    glTranslatef(0,0,AXES_LEN);
    gluCylinder(objCylinder,0.3, 0.0, 0.6, 10, 5);                 //X
    glPopMatrix();
    glPushMatrix();
    //    glTranslatef(AXES_LEN,0.5,0);
    //    GLPrint("X");                                               // Print GL Text ToThe Screen
    glPopMatrix();
}

void Widget::drawMyCube()
{

//    glScalef(xRot*_far, yRot*_far, zRot*_far);
    glTranslatef(  0.0,  0.0, -5.0 );
    glRotatef( xRot,  1.0,  0.0,  0.0 );
    glRotatef( yRot,  0.0,  1.0,  0.0 );
    glRotatef( zRot,  0.0,  0.0,  1.0 );
    glBegin( GL_QUADS );
    glColor3f( 0.0, 1.0, 0.0 );
    glVertex3f(  1.0,  1.0, -1.0 );
    glVertex3f( -1.0,  1.0, -1.0 );
    glVertex3f( -1.0,  1.0,  1.0 );
    glVertex3f(  1.0,  1.0,  1.0 );

    glColor3f( 1.0, 0.5, 0.0 );
    glVertex3f(  1.0, -1.0,  1.0 );
    glVertex3f( -1.0, -1.0,  1.0 );
    glVertex3f( -1.0, -1.0, -1.0 );
    glVertex3f(  1.0, -1.0, -1.0 );

    glColor3f( 1.0, 0.0, 0.0 );
    glVertex3f(  1.0,  1.0,  1.0 );
    glVertex3f( -1.0,  1.0,  1.0 );
    glVertex3f( -1.0, -1.0,  1.0 );
    glVertex3f(  1.0, -1.0,  1.0 );

    glColor3f( 1.0, 1.0, 0.0 );
    glVertex3f(  1.0, -1.0, -1.0 );
    glVertex3f( -1.0, -1.0, -1.0 );
    glVertex3f( -1.0,  1.0, -1.0 );
    glVertex3f(  1.0,  1.0, -1.0 );

    glColor3f( 0.0, 0.0, 1.0 );
    glVertex3f( -1.0,  1.0,  1.0 );
    glVertex3f( -1.0,  1.0, -1.0 );
    glVertex3f( -1.0, -1.0, -1.0 );
    glVertex3f( -1.0, -1.0,  1.0 );

    glColor3f( 1.0, 0.0, 1.0 );
    glVertex3f(  1.0,  1.0, -1.0 );
    glVertex3f(  1.0,  1.0,  1.0 );
    glVertex3f(  1.0, -1.0,  1.0 );
    glVertex3f(  1.0, -1.0, -1.0 );
    glEnd();
}

void Widget::drawAxis()
{
    glTranslatef(  0.0,  0.0, -40.0 );
    glRotatef( xRot,  1.0,  0.0,  0.0 );
    glRotatef( yRot,  0.0,  1.0,  0.0 );
    glRotatef( zRot,  0.0,  0.0,  1.0 );

    glBegin( GL_LINES );
    glEnable(GL_LINE_SMOOTH);
    glColor3f( 1.0, 0.0, 1.0 );
    for(int i=-10;i<=10;i++) {
        glVertex3f(-10, 0, i);
        glVertex3f(10, 0, i);
        glVertex3f(i, 0, -10);
        glVertex3f(i, 0, 10);
    }
    glVertex3f(10, 10, 10);
    glVertex3f(10, 0, 10);

    glVertex3f(-10, 10, 10);
    glVertex3f(-10, 0, 10);

    glVertex3f(10, 10, -10);
    glVertex3f(10, 0, -10);

    glVertex3f(-10, 10, -10);
    glVertex3f(-10, 0, -10);

    glEnd();
}

void Widget::initializeGL()
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

void Widget::paintGL()
{
    //清除屏幕和深度缓存
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    //重置当前的模型观察矩阵
    glLoadIdentity();

    drawAxis();
}

void Widget::resizeGL(int width, int height)
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

void Widget::keyPressEvent(QKeyEvent *e)
{
    switch(e->key()) {
    case Qt::Key_W:
        xRot++;
        updateGL();
        break;
    case Qt::Key_S:
        xRot--;
        updateGL();
        break;
    case Qt::Key_D:
        yRot++;
        updateGL();
        break;
    case Qt::Key_A:
        yRot--;
        updateGL();
        break;
    case Qt::Key_E:
        zRot++;
        updateGL();
        break;
    case Qt::Key_Q:
        zRot--;
        updateGL();
        break;
    case Qt::Key_Z:
        _far+=0.1;
        updateGL();
        break;
    case Qt::Key_X:
        _far-=0.1;
        updateGL();
        break;
    default:
        break;
    }
}
