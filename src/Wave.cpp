#include <QtOpenGL>
#include <QVector3D>
#include "Wave.h"

#include <QDebug>

Color color(double u, double min, double max);

Wave::Wave(QString data, MainWindow *mainWindow, const QVector3D& center, QObject *parent):
    Object3D(mainWindow, center, parent)
{
    readData(data);

    time = 0;
    ratio = 1;
    playing = false;
    origin = mainWindow->actionOrigin->isChecked();
    colorAsVelocity = mainWindow->actionVelocity->isChecked();

    spinBoxTime = new QDoubleSpinBox();
    spinBoxTime->setDecimals(3);
    spinBoxTime->setSingleStep(0.005);

    mainWindow->toolBar->addWidget(spinBoxTime);

    connect(mainWindow->actionOrigin, SIGNAL(toggled(bool)), this, SLOT(drawOriginToggle(bool)));
    connect(mainWindow, SIGNAL(rewindWave()), this, SLOT(rewind()));
    connect(mainWindow->actionSlower, SIGNAL(triggered()), this, SLOT(slower()));
    connect(mainWindow->actionPlayPause, SIGNAL(triggered()), this, SLOT(playingToggle()));
    connect(mainWindow->actionFaster, SIGNAL(triggered()), this, SLOT(faster()));
    connect(mainWindow, SIGNAL(forwardWave()), this, SLOT(forward()));
    connect(mainWindow->actionVelocity, SIGNAL(triggered()), this, SLOT(colorAsVelocityToggle()));
    connect(spinBoxTime, SIGNAL(valueChanged(double)), this, SLOT(changeTime(double)));

    connect(&timer, SIGNAL(timeout()), this, SLOT(increaseTime()));
}

void Wave::drawGeometry()const
{
    if(origin)
        drawOrigin();

    int k = time * 200;

    /*if(playing)
        k = (int) (time * (disc_t / (ratio * (end_t - start_t) * 25))) % disc_t;
    else
        k = spinBoxTime->value() * 200;*/

    for(int i = 0 ; i < disc_x - 1 ; i++)
    {
        for(int j = 0 ; j < disc_y - 1 ; j++)
        {
            Color c[4];
            Vector normal[4];
            Point previous_i[4], sucessor_i[4];
            Point previous_j[4], sucessor_j[4];

            if(i > 0 && i < disc_x - 2)
            {
                // Vertex 0
                previous_i[0] = vertex_matrix[i-1][j][k];
                sucessor_i[0] = vertex_matrix[i+1][j][k];
                // Vertex 1
                previous_i[1] = vertex_matrix[i][j][k];
                sucessor_i[1] = vertex_matrix[i+2][j][k];
                // Vertex 2
                previous_i[2] = vertex_matrix[i][j+1][k];
                sucessor_i[2] = vertex_matrix[i+2][j+1][k];
                // Vertex 3
                previous_i[3] = vertex_matrix[i-1][j+1][k];
                sucessor_i[3] = vertex_matrix[i+1][j+1][k];
            }
            else if(i == 0)
            {
                // Vertex 0
                previous_i[0] = vertex_matrix[i][j][k];
                sucessor_i[0] = vertex_matrix[i+1][j][k];
                // Vertex 1
                previous_i[1] = vertex_matrix[i][j][k];
                sucessor_i[1] = vertex_matrix[i+2][j][k];
                // Vertex 2
                previous_i[2] = vertex_matrix[i][j+1][k];
                sucessor_i[2] = vertex_matrix[i+2][j+1][k];
                // Vertex 3
                previous_i[3] = vertex_matrix[i][j+1][k];
                sucessor_i[3] = vertex_matrix[i+1][j+1][k];
            }
            else
            {
                // Vertex 0
                previous_i[0] = vertex_matrix[i-1][j][k];
                sucessor_i[0] = vertex_matrix[i+1][j][k];
                // Vertex 1
                previous_i[1] = vertex_matrix[i][j][k];
                sucessor_i[1] = vertex_matrix[i+1][j][k];
                // Vertex 2
                previous_i[2] = vertex_matrix[i][j+1][k];
                sucessor_i[2] = vertex_matrix[i+1][j+1][k];
                // Vertex 3
                previous_i[3] = vertex_matrix[i-1][j+1][k];
                sucessor_i[3] = vertex_matrix[i+1][j+1][k];
            }

            if(j > 0 && j < disc_y - 2)
            {
                // Vertex 0
                previous_j[0] = vertex_matrix[i][j-1][k];
                sucessor_j[0] = vertex_matrix[i][j+1][k];
                // Vertex 1
                previous_j[1] = vertex_matrix[i+1][j-1][k];
                sucessor_j[1] = vertex_matrix[i+1][j+1][k];
                // Vertex 2
                previous_j[2] = vertex_matrix[i+1][j][k];
                sucessor_j[2] = vertex_matrix[i+1][j+2][k];
                // Vertex 3
                previous_j[3] = vertex_matrix[i][j][k];
                sucessor_j[3] = vertex_matrix[i][j+2][k];
            }
            else if(j == 0)
            {
                // Vertex 0
                previous_j[0] = vertex_matrix[i][j][k];
                sucessor_j[0] = vertex_matrix[i][j+1][k];
                // Vertex 1
                previous_j[1] = vertex_matrix[i+1][j][k];
                sucessor_j[1] = vertex_matrix[i+1][j+1][k];
                // Vertex 2
                previous_j[2] = vertex_matrix[i+1][j][k];
                sucessor_j[2] = vertex_matrix[i+1][j+2][k];
                // Vertex 3
                previous_j[3] = vertex_matrix[i][j][k];
                sucessor_j[3] = vertex_matrix[i][j+2][k];
            }
            else
            {
                // Vertex 0
                previous_j[0] = vertex_matrix[i][j-1][k];
                sucessor_j[0] = vertex_matrix[i][j+1][k];
                // Vertex 1
                previous_j[1] = vertex_matrix[i+1][j-1][k];
                sucessor_j[1] = vertex_matrix[i+1][j+1][k];
                // Vertex 2
                previous_j[2] = vertex_matrix[i+1][j][k];
                sucessor_j[2] = vertex_matrix[i+1][j+1][k];
                // Vertex 3
                previous_j[3] = vertex_matrix[i][j][k];
                sucessor_j[3] = vertex_matrix[i][j+1][k];
            }

            for(int n = 0 ; n < 4 ; n++)
            {
                Vector a(previous_i[n], sucessor_i[n]);
                Vector b(previous_j[n], sucessor_j[n]);
                normal[n] = a.normal(b);
            }

            if(!colorAsVelocity)
            {
                c[0] = color(vertex_matrix[i][j][k].getZ(), min_u, max_u);
                c[1] = color(vertex_matrix[i+1][j][k].getZ(), min_u, max_u);
                c[2] = color(vertex_matrix[i+1][j+1][k].getZ(), min_u, max_u);
                c[3] = color(vertex_matrix[i][j+1][k].getZ(), min_u, max_u);
            }
            else
            {
                c[0] = color(velocity[i][j], min_v, max_v);
                c[1] = color(velocity[i+1][j], min_v, max_v);
                c[2] = color(velocity[i+1][j+1], min_v, max_v);
                c[3] = color(velocity[i][j+1], min_v, max_v);
            }

            glBegin( GL_QUADS );
                glColor3d(c[0].getRed(), c[0].getGreen(), c[0].getBlue());
                glNormal3d(normal[0].getDirection().getX(), normal[0].getDirection().getY(), normal[0].getDirection().getZ());
                glVertex3d(vertex_matrix[i][j][k].getX(), vertex_matrix[i][j][k].getY(), vertex_matrix[i][j][k].getZ());

                glColor3d(c[1].getRed(), c[1].getGreen(), c[1].getBlue());
                glNormal3d(normal[1].getDirection().getX(), normal[1].getDirection().getY(), normal[1].getDirection().getZ());
                glVertex3d(vertex_matrix[i+1][j][k].getX(), vertex_matrix[i+1][j][k].getY(), vertex_matrix[i+1][j][k].getZ());

                glColor3d(c[2].getRed(), c[2].getGreen(), c[2].getBlue());
                glNormal3d(normal[2].getDirection().getX(), normal[2].getDirection().getY(), normal[2].getDirection().getZ());
                glVertex3d(vertex_matrix[i+1][j+1][k].getX(), vertex_matrix[i+1][j+1][k].getY(), vertex_matrix[i+1][j+1][k].getZ());

                glColor3d(c[3].getRed(), c[3].getGreen(), c[3].getBlue());
                glNormal3d(normal[3].getDirection().getX(), normal[3].getDirection().getY(), normal[3].getDirection().getZ());
                glVertex3d(vertex_matrix[i][j+1][k].getX(), vertex_matrix[i][j+1][k].getY(), vertex_matrix[i][j+1][k].getZ());
            glEnd();
        }
    }
}

void Wave::drawOrigin()const
{

    glDisable( GL_LIGHTING );
    glBegin( GL_LINES );
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(1.0, 0.0, 0.0);

        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 1.0, 0.0);

        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 1.0);
    glEnd();
    glEnable( GL_LIGHTING );
}

void Wave::readData(QString data)
{
    std::ifstream file(data.toAscii());

    file >> start_x >> end_x >> disc_x;
    file >> start_y >> end_y >> disc_y;
    file >> start_t >> end_t >> disc_t;

    u = (double ***) malloc(sizeof(double **) * disc_y);
    for (int i = 0 ; i < disc_y ; i++)
    {
        u[i] = (double **) malloc(sizeof(double *) * disc_x);
        for (int j = 0 ; j < disc_x ; j++)
            u[i][j] = (double *) malloc(sizeof(double) * disc_t);
    }

    min_u = 100;
    max_u = -100;

    for (int i = 0; i < disc_t; i++)
    {
        for (int j = 0; j < disc_x; j++)
        {
            for(int k = 0 ; k < disc_y ; k++)
            {
                file >> u[j][k][i];

                min_u = u[j][k][i] < min_u ? u[j][k][i] : min_u;
                max_u = u[j][k][i] > max_u ? u[j][k][i] : max_u;
            }
        }
    }

    delta_x = (end_x - start_x) / (disc_x - 1);
    delta_y = (end_y - start_y) / (disc_y - 1);
    delta_t = 0.04;


    vertex_matrix = (Point ***) malloc(sizeof(Point **) * disc_y);
    for (int i = 0 ; i < disc_y ; i++)
    {
        vertex_matrix[i] = (Point **) malloc(sizeof(Point *) * disc_x);
        for (int j = 0 ; j < disc_x ; j++)
            vertex_matrix[i][j] = (Point *) malloc(sizeof(Point) * disc_t);
    }

    for (int i = 0; i < disc_x; i++)
    {
        for (int j = 0; j < disc_y; j++)
        {
            for (int k = 0 ; k < disc_t ; k++)
            {
                vertex_matrix[i][j][k].setX(start_x + i * delta_x);
                vertex_matrix[i][j][k].setY(start_y + j * delta_y);
                vertex_matrix[i][j][k].setZ(u[i][j][k]);
            }
        }
    }

    velocity = (double **) malloc(sizeof(double *) * disc_x);
    for(int i = 0 ; i < disc_x ; i++)
        velocity[i] = (double *) malloc(sizeof(double) * disc_y);

    min_v = 100;
    max_v = -100;

    for (int i = 0; i < disc_x; i++)
    {
        for (int j = 0; j < disc_y; j++)
        {
            file >> velocity[i][j];

            min_v = velocity[i][j] < min_v ? velocity[i][j] : min_v;
            max_v = velocity[i][j] > max_v ? velocity[j][j] : max_v;
        }
    }
}

void Wave::increaseTime()
{
    switch(ratio)
    {
        case 1:
            time += 0.04;
            break;
        case 2:
            time += 0.02;
            break;
        case 4:
            time += 0.01 ;
            break;
        case 8:
            time += 0.005 ;
            break;
    }

    if(time > end_t)
        time = 0;

    spinBoxTime->setValue(time);
}

void Wave::rewind()
{
    if(playing)
    {
        timer.stop();
        playing = false;
    }
    time = 0;
}

void Wave::slower()
{
    if(ratio != 8)
        ratio *= 2;
}

void Wave::playingToggle()
{
    if(playing)
    {
        timer.stop();
        playing = false;
    }
    else
    {
        timer.start(40);
        playing = true;
    }
}

void Wave::faster()
{
    if(ratio != 1)
        ratio /= 2;
}

void Wave::forward()
{
    if(playing)
    {
        timer.stop();
        playing = false;
    }
    time = disc_t;
}

void Wave::colorAsVelocityToggle()
{
    if(colorAsVelocity)
        colorAsVelocity = false;
    else
        colorAsVelocity = true;
}

void Wave::changeTime(double time)
{
    if(time >= 0 && time <= end_t)
        this->time = time;
    else
    {
        if(time < 0)
            spinBoxTime->setValue(0);
        else
            spinBoxTime->setValue(end_t);
    }
}

Color color(double u, double min, double max)
{
    Color c;

    u *= 10;
    /*if(u == 0)
    {
        c.setRGB(0, 1.0, 0);
        return c;
    }*/

    u = (u - (min + ((max - min)/2))) / ((max - min)/2);

    if(u < -1)
        c.setRGB(0, 0, 1);
    else if(u >= -1.0 && u < -0.5)
        c.setRGB(0, ((u+1.0) * 2.0), 1);
    else if(u >= -0.5 && u < 0.0)
        c.setRGB(0, 1, (1-((u+0.5) * 2.0)));
    else if(u >= 0.0 && u < 0.5)
        c.setRGB(u*2.0, 1, 0);
    else if(u >= 0.5 && u < 1.0)
        c.setRGB(1, (1-((u-0.5) * 2)), 0);
    else if(u >= 1.0)
        c.setRGB(1, 0, 0);

    return c;
}
