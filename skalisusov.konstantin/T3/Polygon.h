#ifndef GITLABPROG_POLYGON_H
#define GITLABPROG_POLYGON_H
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
    std::vector<Point> polygon_;
  };
}
#endif //GITLABPROG_POLYGON_H
