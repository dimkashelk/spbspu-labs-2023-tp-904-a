#ifndef COMMANDS_H
#define COMMANDS_H
#include <map>
#include <vector>
#include <iostream>
namespace aksenov
{
  using dictOfTranslations = std::map< std::string, std::vector< std::string > >;
  using dictOfDicts = std::map< std::string, dictOfTranslations >;

  std::string insertCommand(std::istream &);

  class Commands
  {
  public:
    Commands();
    void doCommand( std::string &command, std::istream &in, dictOfDicts &dict, std::ostream &out);
  private:
    std::map< std::string, void(*)(std::string &, std::istream &, dictOfDicts &, std::ostream &)> dict_;
  };
  void executeCommand(std::ostream &out, std::istream &in, Commands &commands, dictOfDicts &dict, std::string command);
}
#endif
