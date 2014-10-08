#include "Scene3D.h"

Scene3D::Scene3D(MainWindow *mainWindow, const QVector3D& center, QObject *parent) :
    Object3D(mainWindow, center, parent), origin(false)
{
}

Scene3D::~Scene3D()
{
    for(int i = 0; i < objects.size(); ++i)
    {
        delete objects[i];
    }
    objects.clear();
}

void Scene3D::drawGeometry(void) const
{
    if(origin)
        drawOrigin();
    for(int i = 0; i < objects.size(); ++i)
        objects[i]->draw();
}

void Scene3D::addObject3D(Object3D* obj)
{
    objects.append(obj);
}

void Scene3D::removeObject3D()
{
    delete objects[0];
}

void Scene3D::drawOrigin() const
{
    GLboolean isLighting;
    GLfloat color[4];
    glGetBooleanv(GL_LIGHTING,&isLighting);
    glGetFloatv(GL_CURRENT_COLOR,color);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);

    //glUseProgram(0);

    glBegin(GL_LINES);
    glColor3f(1.0, 0, 0);
    glVertex3i(1, 1, 1);
    glVertex3i(1, 0, 0);

    glColor3f(0, 1.0, 0);
    glVertex3i(1, 1, 1);
    glVertex3i(0, 1, 0);

    glColor3f(0, 0, 1.0);
    glVertex3i(1, 1, 1);
    glVertex3i(0, 0, 1);
    glEnd();

    glEnable(GL_TEXTURE_2D);
    glColor4fv(color);
    if(isLighting)
        glEnable(GL_LIGHTING);
}
