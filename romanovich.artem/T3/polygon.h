#ifndef POLYGON_H
#define POLYGON_H
#include <vector>
#include <cstddef>
#include "point.h"
class Polygon
{
public:
  explicit Polygon(const std::vector< Point > &points);
  size_t getPointsCount() const;
  Point getPoint(size_t index) const;
  double getArea() const;
  struct AreaComp
  {
    bool operator()(const Polygon &lhs, const Polygon &rhs) const
    {
      return lhs.getArea() < rhs.getArea();
    }
  };
  struct VertexCountComp
  {
    bool operator()(const Polygon &lhs, const Polygon &rhs) const
    {
      return lhs.getPointsCount() < rhs.getPointsCount();
    }
  };
private:
  std::vector< Point > points_;
};
#endif
