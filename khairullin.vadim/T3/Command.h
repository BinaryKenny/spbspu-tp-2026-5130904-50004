#ifndef COMMAND_H
#define COMMAND_H
#include "Polygon.h"
#include "Functions.h"

namespace khairullin {
  struct Command {
    using func_t = void(Command::*)(std::istream &) const;

    std::vector< Polygon > polygons;
    std::unordered_map< std::string, func_t > commands;

    Command();

    void function(std::istream &) const;

    void area(std::istream &) const;
    void max(std::istream &) const;
    void min(std::istream &) const;
    void count(std::istream &) const;
    void intersection(std::istream &) const;
    void same(std::istream &) const;
  };
}
#endif //COMMAND_H
