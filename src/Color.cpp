#include "Color.h"

Color::Color()
{
}

double Color::getRed()
{
    return red;
}
void Color::setRed(double red)
{
    this->red = red;
}

double Color::getGreen()
{
    return green;
}
void Color::setGreen(double green)
{
    this->green = green;
}

double Color::getBlue()
{
    return blue;
}
void Color::setBlue(double blue)
{
    this->blue = blue;
}

void Color::setRGB(double red, double green, double blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
}
