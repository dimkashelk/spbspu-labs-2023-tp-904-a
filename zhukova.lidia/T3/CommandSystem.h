#ifndef T3_COMMANDSYSTEM_H
#define T3_COMMANDSYSTEM_H
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include "Geometry.h"
#include "Commands.h"
namespace zhukova
{
  struct CommandSystem
  {
    std::map< std::string, void (*)(const std::vector< Polygon > & src, std::ostream & out) > dict;
    std::map< std::string, void (*)(const std::vector< Polygon > & src, size_t number,
                                    std::ostream & out) > dictNumber;
    std::map< std::string, void (*)(std::vector< Polygon > & src, const Polygon & pol,
                                    std::ostream & out) > dictPolygon;
  };
  CommandSystem makeCommandSystem();
  void doCommand(std::vector< Polygon > & src, const CommandSystem & cs,
                 const std::string & command,
                 std::ostream & out);
  std::string inputCommand(std::istream & in);
}
#endif
