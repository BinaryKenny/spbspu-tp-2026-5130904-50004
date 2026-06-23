#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include "Point.h"
#include "Frame.h"

namespace khairullin {
  struct Polygon {
    std::vector< Point > points;

    double area() const;
    Frame getFrame() const;
    bool cross(const Polygon & other) const;
    bool operator==(const Polygon & other) const;
  };
}
#endif //POLYGON_H
