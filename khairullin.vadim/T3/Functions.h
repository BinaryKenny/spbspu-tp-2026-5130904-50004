#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "Polygon.h"
#include "Delimiter.h"
#include <string>
#include <sstream>
#include <iostream>

using point_iter = std::istream_iterator< khairullin::Point >;

namespace khairullin {
  std::istream & operator>>(std::istream & is, Delimiter && del);
  std::istream & operator>>(std::istream & is, Polygon & polygon);
  std::istream & operator>>(std::istream & is, Point & point);
  std::ostream & operator<<(std::ostream & os, const Polygon & polygon);
  std::ostream & operator<<(std::ostream & os, const Point & point);

  bool isEqualTo(const Polygon & polygon, const size_t vertexes);
  bool hasCrossing(const Polygon & p1, const Polygon & p2);
}
#endif //FUNCTIONS_H
