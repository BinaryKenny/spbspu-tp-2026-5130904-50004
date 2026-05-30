#ifndef POINT_H
#define POINT_H

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
}
#endif //POINT_H
