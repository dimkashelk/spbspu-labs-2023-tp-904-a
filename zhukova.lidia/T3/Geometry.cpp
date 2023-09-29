#include "Geometry.h"
namespace zhukova
{
  bool PointComparator::operator()(const Point & lhs, const Point & rhs)
  {
    return (lhs.x == rhs.x) && (lhs.y == rhs.y);
  }
  bool PolygonComparator::operator()(const Polygon & lhs, const Polygon & rhs)
  {
    if (getAmountOfVertexes(lhs) == getAmountOfVertexes(rhs))
    {
      return std::equal(lhs.points.begin(),
                        lhs.points.end(),
                        rhs.points.begin(),
                        PointComparator());
    }
    return false;
  }
  bool isOddVertexes(const Polygon & src)
  {
    return src.points.size() % 2 == 1;
  }
  bool isEvenVertexes(const Polygon & src)
  {
    return !isOddVertexes(src);
  }
  size_t getAmountOfVertexes(const Polygon & src)
  {
    return src.points.size();
  }
  bool isAmountOfVertexes(const Polygon & src, size_t amount)
  {
    return amount == getAmountOfVertexes(src);
  };
  int shoelaceAlgorithm(const Point & p1, const Point & p2)
  {
    return p1.x * p2.y - p1.y * p2.x;
  }
  double getArea(const Polygon & src)
  {
    std::vector< int > sumStages;
    std::transform(
      src.points.begin(),
      --src.points.end(),
      ++src.points.begin(),
      std::back_inserter(sumStages),
      shoelaceAlgorithm);
    sumStages.push_back(shoelaceAlgorithm(src.points[src.points.size() - 1], src.points[0]));
    return abs(std::accumulate(sumStages.begin(), sumStages.end(), 0.0)) / 2.0;
  }
  double getAreaIf(const Polygon & src, bool (* pred)(const Polygon &))
  {
    return pred(src) ? getArea(src) : 0.0;
  }
  double getAreaIfVertexes(const Polygon & src, size_t amount, bool (* pred)(const Polygon &, size_t amount))
  {
    return pred(src, amount) ? getArea(src) : 0.0;
  }
  bool isLessArea(const Polygon & src, double area)
  {
    return getArea(src) < area;
  }
}
