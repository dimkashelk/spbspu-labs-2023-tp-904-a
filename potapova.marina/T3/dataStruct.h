#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <vector>
#include <iostream>

namespace potapova
{
  struct Point
  {
    int x, y;
  };

  struct Polygon
  {
    std::vector< Point > points;
  };

  struct DelimiterIO
  {
    char sign;
  };

  bool operator==(const Point& first, const Point& second) noexcept;
  bool operator==(const Polygon& first, const Polygon& second) noexcept;
  std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
  std::istream& operator>>(std::istream& in, Point& dest);
  std::ostream& operator<<(std::ostream& out, const Point& source);
  std::istream& operator>>(std::istream& in, Polygon& dest);
  std::ostream& operator<<(std::ostream& out, Polygon& source);
}

#endif
