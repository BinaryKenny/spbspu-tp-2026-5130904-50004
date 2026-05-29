#ifndef COMMAND_H
#define COMMAND_H
#include "Polygon.h"
#include "Functions.h"

namespace khairullin {
  struct Command {
    using func_t = void(Command::*)(std::istream &);

    std::vector< Polygon > polygons;
    std::unordered_map< std::string, func_t > commands;

    Command();

    void function(std::istream &);

    void area(std::istream &);
    void max(std::istream &);
    void min(std::istream &);
    void count(std::istream &);
    void intersection(std::istream &);
    void same(std::istream &);
  };
}
#endif //COMMAND_H
