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

void khairullin::Command::function(std::istream & is)
{
  std::string command;
  std::getline(is, command, ' ');
  func_t func = commands[command];
  if (func == nullptr) {
    std::cout << "<INVALID COMMAND>\n";
    return;
  }
  try {
    (this->*func)(is);
  }
  catch (std::logic_error & e) {
    std::cout << e.what() << "\n";
  }
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
    auto isEven = std::bind(parity, _1, 0);
    count = std::count_if(polygons.begin(), polygons.end(), isEven);
  }
  else if (parameter == "ODD") {
    auto isOdd = std::bind(parity, _1, 1);
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
  iss >> polygon;
  if (polygon.points.empty()) {
    throw std::logic_error("<INVALID COMMAND>");
  }
  auto cmp = std::bind(hasCrossing, _1, polygon);
  size_t count = std::count_if(polygons.begin(), polygons.end(), cmp);
  std::cout << count << "\n";
}

void khairullin::Command::same(std::istream & is)
{
  Polygon pol;
  std::string line = "";
  std::getline(is, line);
  std::istringstream iss(line);
  iss >> pol;
  if (pol.points.empty()) {
    throw std::logic_error("<INVALID COMMAND>");
  }
  Frame frame1 = pol.getFrame();
  int del_X = frame1.pos.x;
  int del_Y = frame1.pos.y;
  auto move = std::bind(movePoint, _1, del_X, del_Y);
  std::transform(pol.points.begin(), pol.points.end(), pol.points.begin(), move);
  std::vector< Polygon > copy = polygons;
  std::transform(copy.begin(), copy.end(), copy.begin(), movePolygon);
  auto cmp = std::bind(std::equal_to<>(), _1, pol);
  size_t count = std::count_if(copy.begin(), copy.end(), cmp);
  std::cout << pol << "\n";
  std::cout << count << "\n";
}