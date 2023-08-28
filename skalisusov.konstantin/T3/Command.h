#ifndef GITLABPROG_COMMAND_H
#define GITLABPROG_COMMAND_H
#include <iostream>
#include <map>
#include <functional>
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
  void errorMessage(std::ostream & out);

  void rmecho(std::vector< Polygon > &dest,std::istream &in, std::ostream &out);

  bool isNumVertex(const Polygon &polygon, std::size_t count);
  bool isEven(const Polygon &poly);
  bool isOdd(const Polygon &poly);
  bool isRects(const Polygon &poly);

  using cmd_const_area = std::function< void (const std::vector< Polygon > &, std::ostream &)>;
  using cmd_const_vertex = std::function< void (const std::vector< Polygon > &, std::size_t &, std::ostream &)>;
  using cmd_area = std::function< void (std::vector< Polygon >&, std::istream &, std::ostream &)>;
  struct commandPolygon
  {
    std::map< std::string, cmd_const_area > const_area;
    std::map< std::string, cmd_const_vertex > const_ver;
    std::map< std::string, cmd_area > area;
  };
  commandPolygon command();
  void realizationCommandPolygon(std::ostream &out,const std::vector< Polygon > &dest,
                                 const commandPolygon  &mapCommand,std::string &command);
  std::string listenCommand(std::istream &in);
}
#endif //GITLABPROG_COMMAND_H
