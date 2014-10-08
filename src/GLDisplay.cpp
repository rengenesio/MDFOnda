#include <QDebug>
#include <QToolTip>
#include "GLDisplay.h"
#include <QMatrix4x4>
#ifdef __APPLE__
    #include <OpenGL/glu.h>
#else
    #include <GL/glu.h>
#endif

#define ZOOMSTEP 0.05

GLDisplay::GLDisplay(QWidget *parent) : QGLWidget(parent),
    rigthPressedPoint(NULLPOINT),
    leftPressedPoint(NULLPOINT), zoom(1.0)
{
    setStyleSheet("border: 2px solid black;");

    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}

GLDisplay::~GLDisplay()
{
}


void GLDisplay::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glEnable( GL_LIGHT0 );
    glEnable( GL_LIGHT1 );

    glEnable(GL_LIGHTING);
    glShadeModel( GL_SMOOTH );
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );	// specify implementation-specific hints

    glClearDepth( 1.0 );					// specify the clear value for the depth buffer
    glDepthFunc( GL_LEQUAL );
    glDisable(GL_CULL_FACE);
    glEnable(GL_NORMALIZE);

    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 0);
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);
}

void GLDisplay::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
}

float GLDisplay::xDist(float aspect)
{
    if(aspect < 1)
        return (0.5)*zoom;
    else
        return (0.5*aspect)*zoom;
}

float GLDisplay::yDist(float aspect)
{
    if(aspect > 1)
        return (0.5)*zoom;
    else
        return (0.5*(1/aspect))*zoom;
}

void GLDisplay::paintGL()
{
    float aspect = width()*1.0/height();

    float xdist = xDist(aspect);
    float ydist = yDist(aspect);

    glClearColor( 0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-xdist*3.0, xdist*3.0, -ydist*3.0, +ydist*3.0, 5.0, 50);

    GLfloat lightPosition0[4];
    lightPosition0[0] = 0;
    lightPosition0[1] = 1;
    lightPosition0[2] = 0;
    lightPosition0[3] = 0;
    GLfloat lightColor0[4];
    lightColor0[0] = 1;
    lightColor0[1] = 1;
    lightColor0[2] = 1;
    lightColor0[3] = 1;
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition0);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glEnable( GL_LIGHT0 );
    GLfloat lightPosition1[4];
    lightPosition1[0] = 0;
    lightPosition1[1] = -1;
    lightPosition1[2] = 0;
    lightPosition1[3] = 0;
    GLfloat lightColor1[4];
    lightColor1[0] = 1;
    lightColor1[1] = 1;
    lightColor1[2] = 1;
    lightColor1[3] = 1;
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glEnable( GL_LIGHT1 );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0,0,-15, 0,0,0, 0,-1,0);

    emit drawModel();

    glFlush();
}

void GLDisplay::mousePressEvent ( QMouseEvent * event )
{
    // Garante que somente 1 botao estara' pressionado e
    //   cancela a operacao anterior caso o outro seja
    //   pressionado
    if(event->button() == Qt::RightButton)
    {
        if(leftPressedPoint != NULLPOINT)
        {
            leftPressedPoint = NULLPOINT;
            rigthPressedPoint = NULLPOINT;
            emit mouseCancel();
        }else
        {
            rigthPressedPoint = event->pos();
        }
        event->accept();
    }else if(event->button() == Qt::LeftButton)
    {
        if(rigthPressedPoint != NULLPOINT)
        {
            leftPressedPoint = NULLPOINT;
            rigthPressedPoint = NULLPOINT;
            emit mouseCancel();
        }else
        {
            leftPressedPoint = event->pos();
        }
        event->accept();
    }else
        event->ignore();
}

void GLDisplay::mouseReleaseEvent ( QMouseEvent * event )
{
    if(event->button() == Qt::RightButton)
    {
        if(rigthPressedPoint != NULLPOINT)
        {
            emit mouseRigthFinish(rigthPressedPoint, event->pos());
            rigthPressedPoint = NULLPOINT;
        }
        event->accept();
    }else if(event->button() == Qt::LeftButton)
    {
        if(leftPressedPoint != NULLPOINT)
        {
            emit mouseLefthFinish(leftPressedPoint, event->pos());
            leftPressedPoint = NULLPOINT;
        }
    }else
        event->ignore();
}

void GLDisplay::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::RightButton)
    {
        if(rigthPressedPoint != NULLPOINT)
        {
            emit mouseRigthMove(rigthPressedPoint, event->pos());
        }
        event->accept();
    }else if(event->buttons() == Qt::LeftButton)
    {
        if(leftPressedPoint != NULLPOINT)
        {
            emit mouseLeftMove(leftPressedPoint, event->pos());
        }
        event->accept();
    }else
        event->ignore();
}

void GLDisplay::wheelEvent(QWheelEvent * event)
{
    int nsteps = event->delta() / (8*15);

    if (event->orientation() == Qt::Vertical) {
        zoom += ZOOMSTEP * nsteps;
        event->accept();
        updateGL();
    }else event->ignore();
 }
