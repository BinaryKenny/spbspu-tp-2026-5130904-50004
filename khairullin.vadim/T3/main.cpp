#include "Polygon.h"
#include <algorithm>
#include "Functions.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include "Command.h"
#include "Polygon.cpp"
#include "Command.cpp"
#include "Functions.cpp"
#include "Point.cpp"
#include "PointCompare.cpp"
using ist_t = std::istream_iterator< khairullin::Polygon >;
using ost_t = std::ostream_iterator< double >;

int main(int argc, char ** argv)
{
  /*std::vector< khairullin::Polygon > polygons;
  if (argc != 2){
    std::cerr << "Unknown parameters\n";
    return 1;
  }
  std::ifstream input(argv[1]);
  std::copy(ist_t{input}, ist_t{}, std::back_inserter(polygons));
  std::copy_if(polygons.begin(), polygons.end(),
    std::ostream_iterator<khairullin::Polygon>(std::cout, "\n"), [&](khairullin::Polygon & p) {
      if (!p.points.empty()) {
        return true;
      }
      return false;
    });
    */
  khairullin::Command program;
  std::ifstream input(argv[1]);
  std::copy_if(ist_t{input}, ist_t{}, std::back_inserter(program.polygons), khairullin::toAdd);
  std::copy(program.polygons.begin(), program.polygons.end(),
    std::ostream_iterator<khairullin::Polygon>(std::cout, "\n"));
  std::cout << std::fixed << std::setprecision(1);
  while (std::cin) {
    program.function(std::cin);
  }
}
