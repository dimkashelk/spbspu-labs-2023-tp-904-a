#ifndef COMMANDS_H
#define COMMANDS_H
#include <map>
#include <string>
#include <vector>
namespace setCommands
{
  using dict = std::map< std::string, std::vector<std::string> >;
  using dictsOfDicts = std::map<std::string, dict>;
  using input = std::map< std::string, void(*)(std::istream&, std::ostream&, dictsOfDicts& ) >;
  void command(input& command);
}
#endif
