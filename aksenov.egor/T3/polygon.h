#ifndef POLYGON_H
#define POLYGON_H
#include <vector>

namespace aksenov
{
  struct Point
  {
    int x, y;
  };
  
  struct Polygon
  {
    std::vector< Point > points;
  };
}
#endif
