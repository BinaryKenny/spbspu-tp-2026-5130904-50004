#include "Command.h"
#include <numeric>

using namespace std::placeholders;

khairullin::Command::Command()
{
  commands.insert({"AREA", &Command::area});
  commands.insert({"MAX", &Command::max});
  commands.insert({"MIN", &Command::min});
  commands.insert({"COUNT", &Command::count});
  commands.insert({"INTERSECTIONS", &Command::intersection});
  commands.insert({"SAME", &Command::same});
}

void khairullin::Command::area(std::istream & is)
{
  std::string parameter;
  std::getline(is, parameter);
  double area = 0;
  if (parameter == "EVEN") {
    area = std::accumulate(polygons.begin(), polygons.end(), 0.0, [](double temp, Polygon & p) {
      if (p.points.size() % 2 == 0) {
        temp += p.area();
      }
      return temp;
    });
  }
  else if (parameter == "ODD") {
    area = std::accumulate(polygons.begin(), polygons.end(), 0.0, [](double temp, Polygon & p) {
      if (p.points.size() % 2 != 0) {
        temp += p.area();
      }
      return temp;
    });
  }
  else {
    size_t vertexes = 0;
    try {
      vertexes = std::stoi(parameter);
    }
    catch (...) {
      throw std::logic_error("<INVALID COMMAND>");
    }
    area = std::accumulate(polygons.begin(), polygons.end(), 0.0, [=](double temp, Polygon & p) {
      if (p.points.size() == vertexes) {
        temp += p.area();
      }
      return temp;
    });
  }
  std::cout << area << "\n";
}

void khairullin::Command::max(std::istream & is)
{
  std::string parameter;
  std::getline(is, parameter);
  double max = 0;
  if (parameter == "AREA") {
    auto BiggestFigure = std::max_element(polygons.begin(), polygons.end(), [](Polygon & p1, Polygon & p2) {
      return p1.area() < p2.area();
    });
    max = (*BiggestFigure).area();
  }
  else {
    size_t vertexes = 0;
    try {
      vertexes = std::stoi(parameter);
    }
    catch (...) {
      throw std::logic_error("<INVALID COMMAND>");
    }
    auto BiggestFigure = std::max_element(polygons.begin(), polygons.end(), [](Polygon & p1, Polygon & p2) {
      return p1.points.size() < p2.points.size();
    });
    max = (*BiggestFigure).points.size();
  }
  std::cout << max << "\n";
}

void khairullin::Command::min(std::istream & is)
{
  std::string parameter;
  std::getline(is, parameter);
  double min = 0;
  if (parameter == "AREA") {
    auto SmallestFigure = std::min_element(polygons.begin(), polygons.end(), [](Polygon & p1, Polygon & p2) {
      return p1.area() < p2.area();
    });
    min = (*SmallestFigure).area();
  }
  else {
    size_t vertexes = 0;
    try {
      vertexes = std::stoi(parameter);
    }
    catch (...) {
      throw std::logic_error("<INVALID COMMAND>");
    }
    auto SmallestFigure = std::min_element(polygons.begin(), polygons.end(), [](Polygon & p1, Polygon & p2) {
      return p1.points.size() < p2.points.size();
    });
    min = (*SmallestFigure).points.size();
  }
  std::cout << min << "\n";
}

void khairullin::Command::count(std::istream & is)
{
  std::string parameter;
  std::getline(is, parameter);
  size_t count = 0;
  if (parameter == "EVEN") {
    auto isEven = std::bind(isEqualTo, _1, 0);
    count = std::count_if(polygons.begin(), polygons.end(), isEven);
  }
  else if (parameter == "ODD") {
    auto isOdd = std::bind(isEqualTo, _1, 1);
    count = std::count_if(polygons.begin(), polygons.end(), isOdd);
  }
  else {
    size_t vertexes = 0;
    try {
      vertexes = std::stoi(parameter);
    }
    catch (...) {
      throw std::logic_error("<INVALID COMMAND>");
    }
    auto cmp = std::bind(isEqualTo, _1, vertexes);
    count = std::count_if(polygons.begin(), polygons.end(), cmp);
  }
  std::cout << count << "\n";
}

void khairullin::Command::intersection(std::istream & is)
{
  std::string line = "";
  std::getline(is, line);
  std::istringstream iss(line);
  Polygon polygon;
  if (!(iss>>polygon)) {
    throw std::logic_error("<INVALID COMMAND>");
  }
  auto cmp = std::bind(hasCrossing, _1, polygon);
  size_t count = std::count_if(polygons.begin(), polygons.end(), cmp);
  std::cout << count << "\n";
}