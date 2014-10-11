#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <math.h>

class Point
{
public:
    Point();
    Point(int x, int y, int layer);

    int X() { return xCoord; }
    int Y() { return yCoord; }
    int Layer() { return dataLayer; }
    void SetLabel (int _label);
    int GetLabel() { return label; }

    bool isLabeled();

    void Print(std::ostream &strm);
    double Distance(Point other);
private:
    int xCoord;
    int yCoord;
    int dataLayer;
    int label;
};

#endif // POINT_H
