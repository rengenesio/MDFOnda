#include "Point.h"

Point::Point()
{
}

Point::Point(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

double Point::getX()
{
    return x;
}
void Point::setX(double x)
{
    this->x = x;
}

double Point::getY()
{
    return y;
}
void Point::setY(double y)
{
    this->y = y;
}

double Point::getZ()
{
    return z;
}
void Point::setZ(double z)
{
    this->z = z;
}

void Point::setXYZ(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

