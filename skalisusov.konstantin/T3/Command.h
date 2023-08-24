#ifndef GITLABPROG_COMMAND_H
#define GITLABPROG_COMMAND_H
#include <iostream>
#include <map>
#include "Polygon.h"
namespace skalisusov
{
  void areaEven(const std::vector< Polygon > &dest, std::ostream &out);
  void areaOdd(const std::vector< Polygon > &dest, std::ostream &out);
  void areaMean(const std::vector< Polygon > &dest, std::ostream &out);
  void areaNumOfVertex(const std::vector< Polygon > &dest,std::size_t vertex ,std::ostream &out);
  void maxArea(const std::vector< Polygon > &dest,std::ostream &out);
  void maxVertex(const std::vector< Polygon > &dest,std::ostream &out);
  void minArea(const std::vector< Polygon > &dest,std::ostream &out);
  void minVertex(const std::vector< Polygon > &dest,std::ostream &out);
  void countEven(const std::vector< Polygon > &dest, std::ostream &out);
  void countOdd(const std::vector< Polygon > &dest, std::ostream &out);
  void countVertex(const std::vector< Polygon > &dest, std::size_t vertex, std::ostream  &out);
  void rects(const std::vector< Polygon > &dest, std::ostream &out);

  void rmecho(std::vector< Polygon > &dest,std::istream &in, std::ostream &out);

  bool isNumVertex(const Polygon &polygon, std::size_t count);
  bool isEven(const Polygon &poly);
  bool isOdd(const Polygon &poly);
  bool isRects(const Polygon &poly);

}
#endif //GITLABPROG_COMMAND_H
