#ifndef T3_POLYGON_HPP
#define T3_POLYGON_HPP
#include <iostream>
#include <vector>
namespace litvin
{
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };
  size_t size(const Polygon & dest);
  double calcAreaIf(bool (*predicate)(const Polygon & pol), const Polygon & dest);
  double calcArea(const Polygon & dest);
  std::istream & operator>>(std::istream & in, Polygon & dest);
  std::istream & operator>>(std::istream & in, Point & dest);
}
#endif
