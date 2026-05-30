#include "Polygon.h"
#include "PointCompare.h"
#include <algorithm>
#include <numeric>

bool khairullin::Frame::operator<(const Frame & other) const
{
  return pos < other.pos;
}

double khairullin::Polygon::area() const
{
  double area = 0;
  std::vector< Point > points_2_to_1(points.size());
  std::copy(points.begin() + 1, points.end(), points_2_to_1.begin());
  points_2_to_1[points.size() - 1] = points[0];
  area = std::inner_product(points.begin(), points.end(),
    points_2_to_1.begin(), 0.0, std::plus<>{}, [&](const Point & p1, const Point & p2) {
      return p1.x * p2.y - p1.y * p2.x;
    });
  area = std::abs(area) / 2;
  return area;
}

khairullin::Frame khairullin::Polygon::getFrame() const
{
  auto pMaxX = std::max_element(points.begin(), points.end(), [&](const Point & p1, const Point & p2) {
    return p1.x < p2.x;
  });
  auto pMaxY = std::max_element(points.begin(), points.end(), [](const Point & p1, const Point & p2) {
    return p1.y < p2.y;
  });
  auto pMinX = std::min_element(points.begin(), points.end(), [](const Point & p1, const Point & p2) {
    return p1.x < p2.x;
  });
  auto pMinY = std::min_element(points.begin(), points.end(), [](const Point & p1, const Point & p2) {
    return p1.y < p2.y;
  });
  int X_max = (*pMaxX).x;
  int Y_max = (*pMaxY).y;
  int X_min = (*pMinX).x;
  int Y_min = (*pMinY).y;
  Point pos{X_min, Y_min};
  return Frame{pos, X_max - X_min, Y_max - Y_min};
}

bool khairullin::Polygon::cross(const Polygon & other) const
{
  Frame frame1 = getFrame();
  Frame frame2 = other.getFrame();
  auto minFrame = std::min(frame1,frame2);
  auto maxFrame = std::max(frame1, frame2);
  if (minFrame.pos.x + minFrame.width >= maxFrame.pos.x &&
    minFrame.pos.y + minFrame.height >= maxFrame.pos.y) {
    return true;
  }
  return false;
}

bool khairullin::Polygon::operator==(Polygon & other) const
{
  if (points.size() != other.points.size()) {
    return false;
  }
  auto copy = *this;
  auto otherCopy = other;
  std::sort(copy.points.begin(), copy.points.end());
  std::sort(otherCopy.points.begin(), otherCopy.points.end());
  return copy.points == otherCopy.points;
}
