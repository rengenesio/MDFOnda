#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include <QGLWidget>
#include <QMouseEvent>
#include <QMoveEvent>
#include <QPoint>
#include <QToolTip>
#include <QMatrix4x4>

#include <GL/glut.h>
#ifdef __APPLE__
    #include <OpenGL/glu.h>
#else
    #include <GL/glu.h>
#endif

#define NULLPOINT   QPoint(-1,-1)
#define EPSILON     0.001

class GLDisplay : public QGLWidget
{
    Q_OBJECT

    QPoint rigthPressedPoint;
    QPoint leftPressedPoint;
    float zoom;


signals:
    void drawModel(void);
    void lightSetup(void);
    void mouseRigthMove(QPoint ini, QPoint curr);
    void mouseRigthFinish(QPoint ini, QPoint curr);
    void mouseLeftMove(QPoint ini, QPoint curr);
    void mouseLefthFinish(QPoint ini, QPoint curr);
    void mouseCancel();

public:
    GLDisplay(QWidget *parent = 0);
    ~GLDisplay();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void mouseMoveEvent(QMouseEvent *);
    void wheelEvent(QWheelEvent * event);
    float xDist(float aspect);
    float yDist(float aspect);

};


#endif // GLDISPLAY_H
