#include <QtOpenGL>
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(QObject *parent)
    : QObject(parent),
      m_rotations(QMatrix4x4()) ,
      m_interactiveQuartenion(QQuaternion())
{
}

void DirectionalLight::setRotations(const QMatrix4x4& rotations)
{
    m_rotations = rotations;
}

const QMatrix4x4& DirectionalLight::rotations(void)const
{
    return m_rotations;
}

void DirectionalLight::setInteractiveQuartenion(const QQuaternion& quaternion)
{
    m_interactiveQuartenion = quaternion;
}

const QQuaternion& DirectionalLight::interactiveQuartenion(void)const
{
    return m_interactiveQuartenion;
}

void DirectionalLight::addRotation(const QQuaternion& rotacao)
{
    QMatrix4x4 m;
    m.rotate(degreeFromCos(rotacao.scalar()), rotacao.x(), rotacao.y(), rotacao.z());
    m_rotations = m*m_rotations;
}

void DirectionalLight::draw(bool d) const
{

   QVector3D lp = getLightPosition();

   GLfloat lightPosition[4];
   lightPosition[0] = lp.x();
   lightPosition[1] = lp.y();
   lightPosition[2] = lp.z();
   lightPosition[3] = 0;

   /*glDisable(GL_LIGHTING);
   glDisable(GL_TEXTURE_2D);
   if(d)
   {
       glBegin(GL_LINES);
       glColor3f(1.0,1.0,0.0);
       glVertex3f(0.0,0.0,0.0);
       glVertex4fv(lightPosition);
       glEnd();
   }
   glEnable(GL_LIGHTING);
   glEnable(GL_TEXTURE_2D);*/

   //glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
}

void DirectionalLight::cleanTransformations()
{
    setInteractiveQuartenion(QQuaternion());
    setRotations(QMatrix4x4());
}

QVector3D DirectionalLight::getLightPosition() const
{
    QQuaternion t = interactiveQuartenion();

    QMatrix4x4 m;
    m.rotate(degreeFromCos(t.scalar()), t.x(), t.y(), t.z());
    m = m*m_rotations;

    return m.mapVector(QVector3D(0,-1000000,0));
}

double DirectionalLight::degreeFromCos(double _cos)const
{
    return (acos(_cos)*180.0)/M_PI;
}
