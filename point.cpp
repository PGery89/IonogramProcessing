#include "point.h"

Point::Point()
{
}

Point::Point(int x, int y, int layer)
{
    xCoord = x;
    yCoord = y;
    dataLayer = layer;
    label = 0;
}

void Point::Print(std::ostream &strm)
{
    strm << "(" << xCoord << ", " << yCoord << "), layer: " << dataLayer << std::endl;
}

void Point::SetLabel(int _label)
{
    label = _label;
}

bool Point::isLabeled()
{
    if(label == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

double Point::Distance(Point other)
{
    double xd = xCoord - other.xCoord;
    double yd = yCoord - other.yCoord;
    return sqrt(xd*xd + yd*yd);
}

