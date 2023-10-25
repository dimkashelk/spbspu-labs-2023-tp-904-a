#ifndef T3_POLYGON_HPP
#define T3_POLYGON_HPP
#include <vector>
#include <iosfwd>

namespace chemodurov
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > data;
  };

  size_t size(const Polygon & pol);
  double calcArea(const Polygon & pol);
  std::istream & operator>>(std::istream & in, Point & dest);
  std::istream & operator>>(std::istream & in, Polygon & dest);
  bool operator==(const Point & lhs, const Point & rhs);
  bool operator!=(const Point & lhs, const Point & rhs);
  bool operator==(const Polygon & lhs, const Polygon & rhs);
  bool operator!=(const Polygon & lhs, const Polygon & rhs);
}

#endif
