#include "PointCompare.h"

#include "Point.h"

bool khairullin::cmpX(const Point & a, const Point & b)
{
  return a.x < b.x;
}

bool khairullin::cmpY(const Point & a, const Point & b)
{
  return a.y < b.y;
}
