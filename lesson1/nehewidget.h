#ifndef NEHEWIDGET_H
#define NEHEWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QGLWidget>
#include <qgl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <QImage>

namespace Ui {
class NeHeWidget;
}

class NeHeWidget : public QGLWidget
{
    Q_OBJECT

public:
    NeHeWidget(QWidget *parent = nullptr);
    NeHeWidget( QWidget* parent = nullptr, const char* name = nullptr, bool fs = false );
    ~NeHeWidget();
protected:
    void initializeGL();
    void paintGL();
    void resizeGL( int width, int height );
    void keyPressEvent(QKeyEvent *e);
    void loadGLTextures();
private:
    Ui::NeHeWidget *ui;
    const char* name = nullptr;
    bool fs = false;
protected:
    bool fullscreen;
    GLfloat rTri;
    GLfloat rQuad;
    GLfloat xRot, yRot, zRot;
    GLuint texture[1];
};

#endif // NEHEWIDGET_H
