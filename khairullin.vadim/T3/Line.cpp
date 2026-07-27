#include "Line.h"

std::istream & khairullin::operator>>(std::istream & is, Line & line)
{
  std::getline(is, line.line);
  return is;
}

std::string khairullin::out(Command & prog, const Line & line)
{
  std::istringstream iss(line.line);
  prog.function(iss);
  return std::string();
}
