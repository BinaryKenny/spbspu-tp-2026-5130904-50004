#include "Functions.h"

std::istream & khairullin::operator>>(std::istream & is, Delimiter && del)
{
  std::istream::sentry s(is);
  if (!s) {
    return is;
  }
  char exp = 0;
  is >> exp;
  if (is && del.expected != exp) {
    is.setstate(std::ios::failbit);
  }
  return is;
}

std::istream & khairullin::operator>>(std::istream & is, Point & point)
{
  std::istream::sentry s(is);
  if (!s) {
    return is;
  }
  int x = 0, y = 0;
  is >> Delimiter{'('} >> point.x >> Delimiter{';'} >> point.y >> Delimiter{')'};
  return is;
}

std::istream & khairullin::operator>>(std::istream & is, Polygon & polygon)
{
  std::istream::sentry s(is);
  if (!s) {
    return is;
  }
  polygon.points.clear();
  size_t vertexes = 0;
  if (!(is >> vertexes)) {
    is.setstate(std::ios::failbit);
    return is;
  }
  std::string line = "";
  std::getline(is, line);
  std::istringstream iss(line);
  std::copy(std::istream_iterator<Point>(iss), std::istream_iterator<Point>{}, std::back_inserter(polygon.points));
  if (vertexes != polygon.points.size()) {
    polygon.points.clear();
  }
  return is;
}

std::ostream & khairullin::operator<<(std::ostream & os, const Polygon & polygon)
{
  os << polygon.points.size();
  std::copy(polygon.points.begin(), polygon.points.end(), std::ostream_iterator<Point>(os));
  return os;
}

std::ostream & khairullin::operator<<(std::ostream & os, const Point & point)
{
  os << ' ' << '(' << point.x << ',' << point.y << ')';
  return os;
}

bool khairullin::isEqualTo(const Polygon & polygon, const size_t vertexes)
{
  return polygon.points.size() == vertexes;
}

bool khairullin::hasCrossing(const Polygon & p1, const Polygon & p2)
{
  if (p1.cross(p2)) {
    return true;
  }
  return false;
}

bool khairullin::parity(const Polygon & polygon, const size_t num)
{
  return polygon.points.size() % 2 == num;
}

khairullin::Point khairullin::movePoint(const Point & point, const int num1, const int num2)
{
  Point p = point;
  p.x -= num1;
  p.y -= num2;
  return p;
}

khairullin::Polygon khairullin::movePolygon(Polygon & p)
{
  Frame frame = p.getFrame();
  int x = frame.pos.x;
  int y = frame.pos.y;
  auto move = std::bind(movePoint, std::placeholders::_1, x, y);
  std::transform(p.points.begin(), p.points.end(), p.points.begin(), move);
  return p;
}
