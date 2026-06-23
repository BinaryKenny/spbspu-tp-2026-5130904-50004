#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "Point.hpp"
#include "Rec_t.hpp"

namespace khairullin
{
  struct Shape
  {
    point_t pos;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(point_t p) = 0;
    virtual void scale(double k) = 0;
    virtual ~Shape() = default;
  };
}
#endif
