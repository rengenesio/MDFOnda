#ifndef WAVE_H
#define WAVE_H

#include <iostream>
#include <fstream>
#include <QTimer>
#include <QtOpenGL>
#include <QVector3D>

#include "Color.h"
#include "MainWindow.h"
#include "Object3D.h"
#include "Vector.h"

#include <GL/glu.h>
#include <GL/glut.h>



class Wave : public Object3D
{
    Q_OBJECT

    int indexList;
public:
    explicit Wave(QString data, MainWindow *mainWindow, const QVector3D& center = QVector3D(), QObject *parent = 0);


private:
    void drawOrigin()const;
    void readData(QString data);

    double ***u;
    double **velocity;
    Point ***vertex_matrix;

    int disc_x, disc_y, disc_t;
    double start_x, end_x, delta_x;
    double start_y, end_y, delta_y;
    double start_t, end_t, delta_t;
    double min_u, max_u;
    double min_v, max_v;

    QTimer timer;
    double time;
    int ratio;
    bool playing;
    bool colorAsVelocity;

    QDoubleSpinBox *spinBoxTime;

protected:
    virtual void drawGeometry()const;

public slots:
    void increaseTime();
    void slower();
    void faster();
    void rewind();
    void playingToggle();
    void forward();
    void colorAsVelocityToggle();
    void changeTime(double time);
};

#endif // WAVE_H
