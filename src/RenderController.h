#ifndef RENDERCONTROLLER_H
#define RENDERCONTROLLER_H

#include <QObject>
#include <QPoint>
#include <QGLContext>
#include <QAction>
#include <QMap>
#include <QList>
#include <QPair>
#include <QTimer>

class DirectionalLight;
class MainWindow;
class Object3D;
class ArcBall;
class Scene3D;

class GLDisplay;

class RenderController : public QObject
{
    Q_OBJECT

    GLDisplay *display;
    Scene3D *scene;
    ArcBall* arcBall;
    DirectionalLight* light;
    bool wireframe;
    bool lightRotation;

public:
    explicit RenderController(MainWindow *mainWindow,
                              QObject *parent = 0);
    ~RenderController();
    QGLWidget* getGLContext(void);
    void updateGL(void);
    QVector3D getLightPosition()const;

private:
    QString saveImage();

    MainWindow *mainWindow;
    QTimer timer;

public slots:
    void drawModel(void);
    void mouseRigthMove(QPoint ini, QPoint curr);
    void mouseRigthFinish(QPoint ini, QPoint curr);
    void mouseLeftMove(QPoint ini, QPoint curr);
    void mouseLefthFinish(QPoint ini, QPoint curr);
    void mouseCancel();
    void saveResultAsImage();
    void lightSetup(void);
    void lightRotationToggle(bool);
    void timeOut();
    void loadWave(QString data);
    void saveWave(QString data);
    void closeScene();
    void wireFrameToggle();

};

#endif // RENDERCONTROLLER_H
