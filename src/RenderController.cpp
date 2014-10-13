#include "RenderController.h"

#include "GLDisplay.h"
#include "MainWindow.h"
#include "Object3D.h"
#include "Arcball.h"
#include "DirectionalLight.h"
#include "Scene3D.h"
#include "Wave.h"

RenderController::RenderController(MainWindow *mainWindow,
                                   QObject *parent):
    QObject(parent)
{
    this->mainWindow = mainWindow;

    light = new DirectionalLight;
    arcBall = new ArcBall(500);
    wireframe = false;
    lightRotation = false;

    this->display = new GLDisplay();
    mainWindow->setGLDisplay(display);
    {  // esta ordem deve ser mantida
        display->updateGL();

        scene = new Scene3D(mainWindow);

        connect(display, SIGNAL(drawModel()), this, SLOT(drawModel()));
        connect(display, SIGNAL(lightSetup()), this, SLOT(lightSetup()));
    }

    connect(display, SIGNAL(mouseLefthFinish(QPoint,QPoint)), this, SLOT(mouseLefthFinish(QPoint,QPoint)));
    connect(display, SIGNAL(mouseLeftMove(QPoint,QPoint)), this, SLOT(mouseLeftMove(QPoint,QPoint)));
    connect(display, SIGNAL(mouseCancel()),
            this, SLOT(mouseCancel()));

    connect(mainWindow, SIGNAL(loadWave(QString)), this, SLOT(loadWave(QString)));
    connect(mainWindow, SIGNAL(saveWave(QString)), this, SLOT(saveWave(QString)));
    connect(mainWindow->actionClose, SIGNAL(triggered()), this, SLOT(closeScene()));
    connect(mainWindow->actionWireFrame, SIGNAL(triggered()), this, SLOT(wireFrameToggle()));

    connect(&timer, SIGNAL(timeout()), this, SLOT(timeOut()));
    timer.start(30);

    mainWindow->showMaximized();
}

RenderController::~RenderController()
{
    delete scene;
    delete display;
    delete arcBall;
}

void RenderController::updateGL(void)
{
    display->updateGL();
}

void RenderController::lightSetup(void)
{
    light->draw(lightRotation);
}

void RenderController::drawModel(void)
{
    if(wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    scene->draw();
}

void RenderController::mouseRigthMove(QPoint begin, QPoint curr)
{
    QVector3D v(curr-begin);
    scene->setTraslation(v/40.0);
    display->updateGL();
}

void RenderController::mouseRigthFinish(QPoint ini, QPoint curr)
{
    QVector3D v(curr-ini);
    scene->setTraslation(QVector3D());
    scene->setCenter(scene->center() + (v/40.0));
    display->updateGL();
}

void RenderController::mouseLeftMove(QPoint ini, QPoint curr)
{
    if(ini == curr)
        return;
    QPoint center(display->width()/2, display->height()/2);

    if(lightRotation)
        light->setInteractiveQuartenion(
                arcBall->rotationForPoints(center,curr, ini));
    else
        scene->setInteractiveQuartenion(
                arcBall->rotationForPoints(center,curr, ini));

    display->updateGL();
}

void RenderController::mouseLefthFinish(QPoint ini, QPoint curr)
{
    if(ini == curr)
        return;
    QPoint center(display->width()/2, display->height()/2);
    QQuaternion t = arcBall->rotationForPoints(center,curr, ini);
    if(lightRotation)
    {
        light->addRotation(t);
        light->setInteractiveQuartenion(QQuaternion());
    }else
    {
        scene->addRotation(t);
        scene->setInteractiveQuartenion(QQuaternion());
    }

    display->updateGL();
}

void RenderController::mouseCancel()
{
    if(lightRotation)
        light->setInteractiveQuartenion(QQuaternion());
    else
        scene->setInteractiveQuartenion(QQuaternion());

    display->updateGL();
}

void RenderController::saveResultAsImage()
{
    QString filePath = saveImage();

    if(filePath.isEmpty())
        return;

    display->updateGL();
    display->grabFrameBuffer().save(filePath);
}

QGLWidget* RenderController::getGLContext(void)
{
    return display;
}

void RenderController::lightRotationToggle(bool lt)
{
    lightRotation = lt;
    display->updateGL();
}

QVector3D RenderController::getLightPosition() const
{
    return light->getLightPosition();
}

QString RenderController::saveImage()
{
    static QString dir = ".";
    QString filename = QFileDialog::getSaveFileName(0,
                                                    "Save Image",
                                                    dir,
                                                    "*.png");
    QString ext = ".png";

    if(filename == ext || filename.isEmpty())
        return QString();

    QFileInfo fi(filename);
    dir = fi.absolutePath();

    if(filename.right(ext.length()) != ext)
        filename += ext;

    return filename;
}

void RenderController::timeOut()
{
    display->updateGL();
}

void RenderController::loadWave(QString data)
{
    Wave *w = new Wave(data, mainWindow);
    scene->addObject3D(w);
}

void RenderController::saveWave(QString fileName)
{
    display->updateGL();
    display->grabFrameBuffer().save(fileName);
}

void RenderController::closeScene()
{
    scene = new Scene3D(mainWindow);
}

void RenderController::wireFrameToggle()
{
    if(wireframe)
        wireframe = false;
    else
        wireframe = true;
}
