#include "Rectangle.hpp"

khairullin::Rectangle::Rectangle(point_t p, double a, double b):
Shape(),
width(a),
length(b),
pos(p)
{}

double khairullin::Rectangle::getArea() const
{
  return width * length;
}

khairullin::rectangle_t khairullin::Rectangle::getFrameRect() const
{
  return khairullin::rectangle_t{pos, width, length};
}

void khairullin::Rectangle::move(point_t p)
{
  pos = p;
}

void khairullin::Rectangle::scale(double k)
{
  width *= k;
  length *= k;
}
