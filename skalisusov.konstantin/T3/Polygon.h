#ifndef GITLABPROG_POLYGON_H
#define GITLABPROG_POLYGON_H
#include <iostream>
#include <vector>

namespace skalisusov
{
  struct Point
  {
    int x;
    int y;
  };
  struct Polygon
  {
    std::vector< Point > polygon;
  };
  struct DelimiterIO
  {
    char delim;
  };
}
#endif //GITLABPROG_POLYGON_H
