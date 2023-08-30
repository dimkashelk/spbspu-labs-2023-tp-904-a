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
    std::vector< Point > shape;
  };
  struct DelimiterIO
  {
    char delim;
  };
  double getArea(const Polygon &polygon);
  bool operator ==(const Point &lhs, const Point &rhs);
  bool operator ==(const Polygon &lhs, const Polygon &rhs);
  bool comparator(const Polygon &lhs, const Polygon &rhs);
  std::istream &operator>>(std::istream &in, Point &point);
  std::istream &operator>>(std::istream &in, Polygon &polygon);
  std::istream &operator>>(std::istream &in, DelimiterIO &&dest);
}
#endif //GITLABPROG_POLYGON_H
