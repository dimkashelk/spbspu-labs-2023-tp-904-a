#ifndef GITLABPROG_COMMAND_HPP
#define GITLABPROG_COMMAND_HPP
#include <functional>
#include <map>
#include "Polygon.hpp"
namespace skalisusov
{
  bool isOdd(const Polygon &rhs);
  bool isEven(const Polygon &rhs);
  bool isRects(const Polygon &rhs);
  void errorMessage(std::ostream &out);
  void outArea(std::ostream &out, double area);
  bool isNumVertex(const Polygon &rhs, size_t count);
  void areaEven(const std::vector< Polygon > &rhs, std::ostream &out);
  void areaOdd(const std::vector< Polygon > &rhs, std::ostream &out);
  void areaMean(const std::vector< Polygon > &rhs, std::ostream &out);
  void maxArea(const std::vector< Polygon > &rhs, std::ostream &out);
  void maxVertex(const std::vector< Polygon > &rhs, std::ostream &out);
  void minArea(const std::vector< Polygon > &rhs, std::ostream &out);
  void minVertex(const std::vector< Polygon > &rhs, std::ostream &out);
  void countEven(const std::vector< Polygon > &rhs, std::ostream &out);
  void countOdd(const std::vector< Polygon > &rhs, std::ostream &out);
  void rects(const std::vector< Polygon > &rhs, std::ostream &out);
  void areaNumOfVertex(const std::vector< Polygon > &rhs, size_t vertex, std::ostream &out);
  void countVertex(const std::vector< Polygon > &rhs, std::size_t vertex, std::ostream  &out);
  void rmecho(std::vector< Polygon > &rhs, std::istream &in, std::ostream &out);

  class Command
  {
  public:
    Command();
    void CommandPolygon(std::istream &in,std::ostream &out, std::vector< Polygon > &rhs,std::string &command);
    std::string listenCommand(std::istream &in);
  private:
    using cmd_const_area = std::function< void (const std::vector< Polygon > &, std::ostream &) >;
    using cmd_const_vertex = std::function< void (const std::vector< Polygon > &, std::size_t &, std::ostream &) >;
    using cmd_area = std::function< void (std::vector< Polygon > &, std::istream &, std::ostream &) >;
    std::map< std::string, cmd_const_area > const_area;
    std::map< std::string, cmd_const_vertex > const_ver;
    std::map< std::string, cmd_area > area;
  };
  size_t do_rmecho(std::vector< Polygon > &rhs, Polygon &lhs);
}
#endif
