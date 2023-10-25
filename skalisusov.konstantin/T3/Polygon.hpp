#ifndef GITLABPROG_POLYGON_HPP
#define GITLABPROG_POLYGON_HPP
#include <vector>
#include <iostream>
#include <StructTypes.hpp>
#include <iofmtguard.hpp>
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
  double getArea(const Polygon &polygon);
  bool operator ==(const Point &lhs, const Point &rhs);
  bool operator ==(const Polygon &lhs, const Polygon &rhs);
  bool comparator(const Polygon &lhs, const Polygon &rhs);
  std::istream &operator>>(std::istream &in, Point &point);
  std::istream &operator>>(std::istream &in, Polygon &polygon);
}
#endif
