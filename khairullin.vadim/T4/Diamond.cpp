#include "Diamond.hpp"

khairullin::Diamond::Diamond(point_t p, double a, double b):
vertDiag(a),
horDiag(b),
pos(p)
{}

double khairullin::Diamond::getArea() const
{
  return vertDiag * horDiag;
}

khairullin::rectangle_t khairullin::Diamond::getFrameRect() const
{
  return rectangle_t{pos, horDiag, vertDiag};
}

void khairullin::Diamond::move(point_t p)
{
  pos = p;
}

void khairullin::Diamond::scale(double k)
{
  vertDiag *= k;
  horDiag *= k;
}

