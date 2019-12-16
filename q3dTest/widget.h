#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGLWidget>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QVector3D>
#include <QKeyEvent>

namespace Ui {
class Widget;
}

class Widget : public QGLWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void GLGrid(QVector3D &pt1, QVector3D &pt2, int num);
    void GLDrawSpaceAxes(void);
    void drawMyCube();
    void drawAxis();
protected:
    void initializeGL();
    void paintGL();
    void resizeGL( int width, int height );
    void keyPressEvent(QKeyEvent *e);

private:
    Ui::Widget *ui;
    GLfloat xRot, yRot, zRot, _far;
};

#endif // WIDGET_H
