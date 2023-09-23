#include "workwithdict.hpp"
#include <map>
#include <iostream>
#include <string>
#include <iotypes.hpp>
#include "command.hpp"
#include "polygon.hpp"

hrushchev::Commands::Commands()
{
  dict1_.insert({"AREA EVEN", getAreaEven});
  dict1_.insert({"AREA ODD", getAreaOdd});
  dict1_.insert({"AREA MEAN", getAreaMean});
  dict2_.insert({"AREA", getAreaVertexes});
  dict1_.insert({"MAX AREA", getMaxArea});
  dict1_.insert({"MAX VERTEXES", getMaxVertexes});
  dict1_.insert({"MIN AREA", getMinArea});
  dict1_.insert({"MIN VERTEXES", getMinVertexes});
  dict1_.insert({"COUNT EVEN", getCountEven});
  dict1_.insert({"COUNT ODD", getCountOdd});
  dict2_.insert({"COUNT", getCountVertexes});
  dict3_.insert({"RMECHO", rmEcho});
  dict3_.insert({"SAME", getSame});
}

void hrushchev::Commands::doCommand(const std::vector< Polygon >& polygons,
  const std::string& cmd,
  std::ostream& out) const
{
  auto func = dict1_.at(cmd);
  func(polygons, out);
}

void hrushchev::Commands::doCommand(const std::vector< Polygon >& polygons,
    const std::string& cmd,
    size_t count,
    std::ostream& out) const
{
  auto func = dict2_.at(cmd);
  func(polygons, count, out);
}

void hrushchev::Commands::doCommand(std::vector< Polygon >& polygons,
    const std::string& cmd,
    const Polygon& polygon,
    std::ostream& out) const
{
  auto func = dict3_.at(cmd);
  func(polygons, polygon, out);
}

std::string hrushchev::inputCommand(std::istream& in)
{
  std::string command = "";
  in >> command;
  if (!in)
  {
    throw std::runtime_error("Error input");
  }
  if ((command != "RMECHO") && (command != "SAME"))
  {
    std::string arg = "";
    in >> arg;
    if (!in)
    {
      throw std::invalid_argument("Error input");
    }
    command = command + " " + arg;
  }
  return command;
}

void hrushchev::doCommand(std::vector< Polygon >& polygons,
    const Commands& dict,
    const std::string& cmd,
    std::ostream& out,
    std::istream& in)
{
  if (cmd == "RMECHO" || cmd == "SAME")
  {
    Polygon polygon;
    in >> polygon >> DelimiterIO{'\n'};
    if (!in)
    {
      throw std::invalid_argument("Error polygon");
    }
    try
    {
      dict.doCommand(polygons, cmd, polygon, out);
      return;
    }
    catch (const std::out_of_range& error)
    {
    }
  }
  try
  {
    dict.doCommand(polygons, cmd, out);
    return;
  }
  catch (const std::out_of_range& error)
  {
  }
  size_t pos = cmd.find(' ');
  size_t count = std::stoull(cmd.substr(pos));
  dict.doCommand(polygons, cmd.substr(0, pos), count, out);
}

