#ifndef COLOR_H
#define COLOR_H

class Color
{
public:
    Color();
    double getRed();
    void setRed(double red);
    double getGreen();
    void setGreen(double green);
    double getBlue();
    void setBlue(double blue);
    void setRGB(double red, double green, double blue);

private:
    double red, green, blue;
};

#endif // COLOR_H
