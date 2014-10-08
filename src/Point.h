#ifndef POINT_H
#define POINT_H

class Point
{
public:
    Point();
    Point(double x, double y, double z);

    double getX();
    void setX(double x);
    double getY();
    void setY(double y);
    double getZ();
    void setZ(double z);

    void setXYZ(double x, double y, double z);

private:
    double x, y, z;
};

#endif // POINT_H
