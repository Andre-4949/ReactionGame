//
// Created by andre on 15.06.2024.
//

#include "../../../include/Scene/HelperClasses/Point.h"


bool helper::Point::smallerXY(int x, int y) {
    return (this->x > x) && (this->y > y);
}

int helper::Point::getX()
{
  return x;
}
int helper::Point::getY()
{
  return y;
}
bool helper::Point::greaterXY(int x, int y) const
{
  return (this->x < x) && (this->y < y);
}

helper::Point::Point(int x, int y) : Point_(x, y), x(x), y(y) {}
