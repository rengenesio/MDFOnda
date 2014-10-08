#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QFileDialog>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

#include "RenderController.h"

class GLDisplay;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setGLDisplay(GLDisplay *);

    QMenuBar *menuBar;
    QMenu *menuFile;
    QAction *actionOpen, *actionSave, *actionClose, *actionExit;
    QMenu *menuOptions;
    QAction *actionOrigin, *actionWireFrame, *actionVelocity;
    QMenu *menuHelp;

    QToolBar *toolBar;
    QAction *actionRewind, *actionSlower, *actionPlayPause, *actionFaster, *actionForward;
    QToolButton *buttonPlayPause;
    bool playing;

    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QWidget *centralWidget;

private:
    void createMenus();
    void createToolBar();
    void createStatusBar();

signals:
    void loadWave(QString fileName);
    void saveWave(QString fileName);
    void rewindWave();
    void forwardWave();

public slots:
    void openFile();
    void saveFile();
    void rewind();
    void closeWave();
    void playingToggle();
    void forward();
};

#endif // MAINWINDOW_H
