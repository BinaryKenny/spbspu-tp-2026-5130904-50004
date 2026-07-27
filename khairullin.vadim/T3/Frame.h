#ifndef FRAME_H
#define FRAME_H
#include "Point.h"
namespace khairullin {
  struct Frame {
    Point pos;
    int width = 0, height = 0;
    Frame() = default;
    Frame(Point pos, int i, int i1):
      pos(pos),
      width(i),
      height(i1)
    {}

    bool operator<(const Frame & other) const
    {
      return pos < other.pos;
    }
  };
}
#endif //FRAME_H
