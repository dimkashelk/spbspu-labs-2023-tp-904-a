#ifndef T2_DATASTRUCT_H
#define T2_DATASTRUCT_H
#include <complex>
#include <vector>
#include <numeric>
namespace zhukova
{
  struct Point
  {
    int x, y;
  };
  struct Polygon
  {
    std::vector< Point > points;
  };
  struct PointComparator
  {
    bool operator()(const Point & lhs, const Point & rhs);
  };
  struct PolygonComparator
  {
    bool operator()(const Polygon & lhs, const Polygon & rhs);
  };
  bool isOddVertexes(const Polygon & src);
  bool isEvenVertexes(const Polygon & src);
  size_t getAmountOfVertexes(const Polygon & src);
  bool isAmountOfVertexes(const Polygon & src, size_t amount);
  int shoelaceAlgorithm(const Point & p1, const Point & p2);
  double getArea(const Polygon & src);
  double getAreaIf(const Polygon & src, bool (* pred)(const Polygon &));
  double getAreaIfVertexes(const Polygon & src, size_t amount, bool (* pred)(const Polygon &, size_t amount));
  bool isLessArea(const Polygon & src, double area);
}
#endif //T2_DATASTRUCT_H
