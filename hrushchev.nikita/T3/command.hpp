#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <vector>
#include "polygon.hpp"

namespace hrushchev
{
  double calcArea(const Point & left, const Point & right);
  double getArea(const Polygon& polygon);

  double getAreaEven(const std::vector< Polygon >& polygons);
  double getAreaOdd(const std::vector< Polygon >& polygons);
  double getAreaMean(const std::vector< Polygon >& polygons);
  double getAreaVertexes(const std::vector< Polygon >& polygons, size_t count);
  double getMaxArea(const std::vector< Polygon >& polygons);
  size_t getMaxVertexes(const std::vector< Polygon >& polygons);
  double getMinArea(const std::vector< Polygon >& polygons);
  size_t getMinVertexes(const std::vector< Polygon >& polygons);
  size_t getCountEven(const std::vector< Polygon >& polygons);
  size_t getCountOdd(const std::vector< Polygon >& polygons);
  size_t getCountVertexes(const std::vector< Polygon >& polygons);
}

#endif
