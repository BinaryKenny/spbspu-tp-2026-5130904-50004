#include "Polygon.h"
#include <algorithm>
#include "Functions.h"
#include <iostream>
#include <fstream>
#include <iterator>
#include "Command.h"
#include "Line.h"
#include "Line.cpp"
#include "Polygon.cpp"
#include "Command.cpp"
#include "Functions.cpp"
#include "Point.cpp"
#include "PointCompare.cpp"
using ist_t = std::istream_iterator< khairullin::Polygon >;
using ost_t = std::ostream_iterator< void >;
using out_t = std::ostream_iterator< std::string >;
using lineIter = std::istream_iterator< khairullin::Line >;

int main(int argc, char ** argv)
{
  if (argc != 2) {
    std::cerr << "Unknown parameters\n";
    return 1;
  }
  khairullin::Command program;
  std::ifstream input(argv[1]);
  std::copy_if(ist_t{input}, ist_t{}, std::back_inserter(program.polygons), khairullin::toAdd);
  std::copy(program.polygons.begin(), program.polygons.end(),
    std::ostream_iterator<khairullin::Polygon>(std::cout, "\n"));
  std::cout << std::fixed << std::setprecision(1);
  auto output = std::bind(khairullin::out, program, _1);
  std::transform(lineIter{std::cin}, lineIter{}, out_t{std::cout}, output);
}
