#ifndef COMMANDS_DICT_HPP
#define COMMANDS_DICT_HPP

#include <vector>
#include <map>
#include <ostream>
#include <istream>

#include "polygon.hpp"

namespace kabanov
{
  using simpleCommandsStorage = std::map< std::string, void(*)(
    const std::vector< kabanov::Polygon >& data, std::ostream& out) >;
  using sizedCommandsStorage = std::map< std::string, void(*)(
    const std::vector< kabanov::Polygon >& data, std::ostream& out, size_t n) >;
  using complexCommandsStorage = std::map< std::string, void(*)(
    const std::vector< kabanov::Polygon >& data, std::ostream& out, std::istream& in) >;
  class CommandContainer
  {
  public:
    CommandContainer();
    void doCommand(std::string command, const std::vector< kabanov::Polygon >& data, std::ostream& out,
      std::istream& in);
    std::string InputCommand(std::istream& in);
  private:
    simpleCommandsStorage simple_commands;
    sizedCommandsStorage sized_commands;
    complexCommandsStorage complex_commands;
    simpleCommandsStorage simpleCommands();
    sizedCommandsStorage sizedCommands();
    complexCommandsStorage complexCommands();
  };
}
#endif
