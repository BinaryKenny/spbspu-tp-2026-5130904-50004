#ifndef LINE_H
#define LINE_H
#include "Command.h"

namespace khairullin {
  struct Line {
    std::string line;
  };

  std::istream & operator>>(std::istream & is, Line & line);
  std::string out(Command & prog, const Line & line);
}

#endif //LINE_H
