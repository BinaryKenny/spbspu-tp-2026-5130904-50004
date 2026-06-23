#ifndef POLYGON_HPP
#define POLYGON_HPP
#include "Shape.hpp"
#include <vector>
#include <cstddef>

namespace khairullin
{
  struct Polygon: Shape
  {
    std::vector<point_t> points;
    Polygon(std::vector<point_t> p);
    virtual double getArea() const;
    virtual rectangle_t getFrameRect() const;
    virtual void move(point_t p);
    virtual void scale(double k);
    virtual ~Polygon() = default;
  };
}
#endif
