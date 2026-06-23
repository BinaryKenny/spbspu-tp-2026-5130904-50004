#ifndef DIAMOND_HPP
#define DIAMOND_HPP
#include "Shape.hpp"
namespace khairullin
{
  struct Diamond: Shape
  {
    double vertDiag, horDiag;
    Diamond(point_t p, double a, double b);
    virtual double getArea() const;
    virtual rectangle_t getFrameRect() const;
    virtual void move(point_t p);
    virtual void scale(double k);
    virtual ~Diamond() = default;
  };
}
#endif
