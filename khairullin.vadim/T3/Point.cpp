#include "Point.h"

khairullin::Point::Point(int x, int y):
  x(x),
  y(y)
{}

khairullin::Point::Point(const Point & other):
  x(other.x),
  y(other.y)
{}

khairullin::Point & khairullin::Point::operator=(const Point & other)
{
  x = other.x;
  y = other.y;
  return *this;
}

bool khairullin::Point::operator<(const Point & other) const
{
  if (x != other.x) {
    return x < other.x;
  }
  if (y != other.y) {
    return y < other.y;
  }
  return false;
}

bool khairullin::Point::operator==(const Point & other) const
{
  return x == other.x && y == other.y;
}

bool khairullin::Point::operator!=(const Point & other) const
{
  return !(*this == other);
}
