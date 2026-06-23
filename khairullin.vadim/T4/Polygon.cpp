#include "Polygon.hpp"
#include <vector>

khairullin::Polygon::Polygon(std::vector<point_t> p):
points(p)
{
  size_t n = p.size();
  double x = 0;
  double y = 0;
  for (size_t i = 0; i < n; i++)
  {
    x += points[i].x;
    y += points[i].y;
  }
  x /= n;
  y /= n;
  pos.x = x;
  pos.y = y;
}

double khairullin::Polygon::getArea() const
{
  size_t n = points.size();
  double area = 0;
  for (size_t i = 0; i < n - 1; i++)
  {
    area += (points[i].x * points[i + 1].y - points[i + 1].x * points[i].y);
  }
  area += (points[n - 1].x * points[0].y - points[0].x * points[n - 1].y);
  area = area < 0 ? area * (-0.5) : area * 0.5;
  return area;
}

khairullin::rectangle_t khairullin::Polygon::getFrameRect() const
{
  size_t n = points.size();
  double x_min = points[0].x;
  double x_max = x_min;
  double y_min = points[0].y;
  double y_max = y_min;
  for (size_t i = 0; i < n; i++)
  {
    if (points[i].x < x_min)
    {
      x_min = points[i].x;
    }
    if (points[i].x > x_max)
    {
      x_max = points[i].x;
    }
    if (points[i].y < y_min)
    {
      y_min = points[i].y;
    }
    if (points[i].y > y_max)
    {
      y_max = points[i].y;
    }
  }
  return khairullin::rectangle_t{pos, x_max - x_min, y_max - y_min};
}

void khairullin::Polygon::move(point_t p)
{
  size_t n = points.size();
  double x = p.x - pos.x;
  double y = p.y - pos.y;
  for (size_t i = 0; i < n; i++)
  {
    points[i].x += x;
    points[i].y += y;
  }
  pos = p;
}

void khairullin::Polygon::scale(double k)
{
  for (size_t i = 0; i < points.size(); i++)
  {
    points[i].x = pos.x + k * (points[i].x - pos.x);
    points[i].y = pos.y + k * (points[i].y - pos.y);
  }
}
