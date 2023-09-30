#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <vector>

#include "polygon.hpp"

namespace kabanov
{
  using polygons = std::vector< kabanov::Polygon >;
  bool isEven(const kabanov::Polygon& pol);
  bool isOdd(const kabanov::Polygon& pol);
  bool isEqualNum(const kabanov::Polygon& pol, size_t num);
  bool isEqualPoint(const kabanov::Point& p1, const kabanov::Point& p2);
  bool isLessVertex(const kabanov::Polygon& lnr, const kabanov::Polygon& rnl);
  bool isRightAngle(const kabanov::Point& a, const kabanov::Point& b, const kabanov::Point& c);
  bool checkRightAngles(const kabanov::Polygon& p);
  size_t countRightShapes(const polygons& data);
  double getTriangleArea(const kabanov::Point& a, const kabanov::Point& b, const kabanov::Point& c);
  bool compareAreas(const kabanov::Polygon& lnr, const kabanov::Polygon& rnl);
  void printAreaEven(const polygons& polygon, std::ostream& out);
  void printAreaOdd(const polygons& polygon, std::ostream& out);
  void printAreaMean(const polygons& polygon, std::ostream& out);
  void printAreaNumOfVertex(const polygons& polygon, std::ostream& out, size_t num);
  void printMaxArea(const polygons& polygon, std::ostream& out);
  void printMinArea(const polygons& polygon, std::ostream& out);
  void printMaxVertex(const polygons& polygon, std::ostream& out);
  void printMinVertex(const polygons& polygon, std::ostream& out);
  void printCountEven(const polygons& polygon, std::ostream& out);
  void printCountOdd(const polygons& polygon, std::ostream& out);
  void printCountNumOfVertex(const polygons& polygon, std::ostream& out, size_t num);
  void printLessArea(const polygons& polygon, std::ostream& out, std::istream& in);
  void printRightShapes(const polygons& polygon, std::ostream& out);
  std::ostream& outInvalidCommandMessage(std::ostream& out);
}
#endif
