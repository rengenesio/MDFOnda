#include "Vector.h"

Vector::Vector()
{
}

Vector::Vector(Point p1, Point p2)
{
    this->origin = p1;
    setDirection(Point(p2.getX() - p1.getX(), p2.getY() - p1.getY(), p2.getZ() - p1.getZ()));
}

Point Vector::getOrigin()
{
    return origin;
}
void Vector::setOrigin(Point p)
{
    origin = p;
}

Point Vector::getDirection()
{
    return direction;
}
void Vector::setDirection(Point p)
{
    direction = p;
}

Vector Vector::normal(Vector v)
{
    Vector n;

    n.setOrigin(origin);

    Point nd;
    nd.setX(direction.getY() * v.getDirection().getZ() -v.getDirection().getY() * direction.getZ());
    nd.setY(v.getDirection().getX() * direction.getZ() - direction.getX() * v.getDirection().getZ());
    nd.setZ(direction.getX() * v.getDirection().getY() - v.getDirection().getX() * direction.getY());

    n.setDirection(nd);

    /*n.setDirectionX(direction_y * v.getDirectionZ() - v.getDirectionY() * direction_z);
    n.setDirectionY(v.getDirectionX() * direction_z - direction_x *  v.getDirectionZ());
    n.setDirectionZ(direction_x * v.getDirectionY() - v.getDirectionX() * direction_y);*/

    return n;
}
