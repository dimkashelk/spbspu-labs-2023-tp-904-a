#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <vector>
#include <iosfwd>

#include "point.hpp"

namespace kabanov
{
  struct Polygon
  {
    std::vector< Point > points;
  };

  double getArea(const Polygon& polygon);

  std::istream& operator>>(std::istream& in, Polygon& polygon);
}
#endif
