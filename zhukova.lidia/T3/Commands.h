#ifndef T3_COMMANDS_H
#define T3_COMMANDS_H
#include <vector>
#include <numeric>
#include <functional>
#include <iterator>
#include <list>
#include "Geometry.h"
#include "DataIO.h"
namespace zhukova
{
  using namespace std::placeholders;
  void getSumAreaOdd(const std::vector< Polygon > & src, std::ostream & out);
  void getSumAreaEven(const std::vector< Polygon > & src, std::ostream & out);
  void getAreaMean(const std::vector< Polygon > & src, std::ostream & out);
  void getSumAreaVertexes(const std::vector< Polygon > & src, size_t vertexes, std::ostream & out);
  void getMaxMinVertexes(const std::vector< Polygon > & src, bool isMax, std::ostream & out);
  void getMaxVertexes(const std::vector< Polygon > & src, std::ostream & out);
  void getMinVertexes(const std::vector< Polygon > & src, std::ostream & out);
  void getMaxMinArea(const std::vector< Polygon > & src, bool isMax, std::ostream & out);
  void getMaxArea(const std::vector< Polygon > & src, std::ostream & out);
  void getMinArea(const std::vector< Polygon > & src, std::ostream & out);
  void countEvenOddVertexes(const std::vector< Polygon > & src, bool isEven, std::ostream & out);
  void countEvenVertexes(const std::vector< Polygon > & src, std::ostream & out);
  void countOddVertexes(const std::vector< Polygon > & src, std::ostream & out);
  void countExactVertexes(const std::vector< Polygon > & src, size_t amount, std::ostream & out);
  void getAmountWithLessArea(std::vector< Polygon > & src, const Polygon & border, std::ostream & out);
  void echo(std::vector< Polygon > & src, const Polygon & pol, std::ostream & out);
}
#endif //T3_COMMANDS_H
