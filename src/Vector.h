#ifndef VECTOR_H
#define VECTOR_H

#include "Point.h"

class Vector
{
public:
    Vector();
    Vector(Point p1, Point p2);

    Point getOrigin();
    void setOrigin(Point p);

    Point getDirection();
    void setDirection(Point p);

    Vector normal(Vector v);

private:
    Point origin;
    Point direction;
};

#endif // VECTOR_H
