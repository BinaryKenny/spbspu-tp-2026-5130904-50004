#ifndef POLYGON_H
#define POLYGON_H
#include <vector>

namespace khairullin {
  struct Point {
    int x = 0, y = 0;

    Point() = default;
    Point(int x, int y);
    Point(const Point & other);
    Point & operator=(const Point & other);

    bool operator<(const Point & other) const;
    bool operator==(const Point & other) const;
    bool operator!=(const Point & other) const;
  };

  struct Frame {
    Point pos;
    size_t width = 0, height = 0;
    Frame() = default;
    Frame(Point pos, int i, int i1):
      pos(pos),
      width(i),
      height(i1)
    {}

    bool operator<(const Frame & other) const;
  };

  struct Polygon {
    std::vector< Point > points;

    double area() const;
    Frame getFrame() const;
    bool cross(const Polygon & other) const;
    bool operator==(Polygon & other) const;
  };
}
#endif //POLYGON_H
