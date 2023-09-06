#ifndef T3_SOLVINGCOMMANDS_H
#define T3_SOLVINGCOMMANDS_H
#include "polygon.h"
#include <vector>
#include <cstddef>

namespace mashkin
{
  using iter = std::vector< Polygon >::iterator;
  struct XMultiY
  {
    XMultiY();
    XMultiY(const Point& first, const Point& second);
    XMultiY operator+(const XMultiY& rhs);
    int res;
  };

  struct PositiveArea
  {
    explicit PositiveArea(const Polygon& lhs);
    std::vector< XMultiY > halfArea;
  };

  struct NegativeArea
  {
    NegativeArea(const Polygon& lhs, const Polygon& rhs);
    std::vector< XMultiY > halfArea;
  };

  struct FullArea
  {
    FullArea();
    FullArea(const PositiveArea& first, const NegativeArea& second);
    FullArea operator+(const FullArea& rhs);
    bool operator<(const FullArea& rhs);
    double res;
  };

  struct Angle
  {
    explicit Angle(const Polygon& rhs);
    std::vector< int > ang;
  };

  std::ostream& operator<<(std::ostream& out, const FullArea& data);

  XMultiY solveXY(const Point& lhs, const Point& rhs);
  PositiveArea calcPositiveArea(const Polygon& lhs);
  NegativeArea calcNegativeArea(const Polygon& lhs);
  FullArea solveArea(const PositiveArea& first, const NegativeArea& second);
  std::vector< FullArea > getFullArea(const iter& begin, const iter& end);
  bool isOdd(const Polygon& data);
  bool isEven(const Polygon& data);
  bool isEqual(const Polygon& data, size_t count);
  bool isEqualPoints(Polygon& lhs, Polygon& rhs);

  int getAngles(const Point& firstPoint, const Polygon& polygon);
  bool isRightShapes(const Polygon& lhs);
}
#endif
