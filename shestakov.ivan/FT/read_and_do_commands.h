#ifndef UNTITLED4_READ_AND_DO_COMMANDS_H
#define UNTITLED4_READ_AND_DO_COMMANDS_H
#include <iostream>
#include <map>
#include "dictionary.h"

namespace shestakov
{
  void doDictsCmds(my_map &dictionaries, const std::string &cmd, std::istream &in, std::ostream &out);
  void doConstDictsCmds(const my_map &dictionaries, const std::string &cmd, std::istream &in, std::ostream &out);
  void doCommand(my_map &dictionaries, const std::string& cmd, std::istream &in, std::ostream &out);
}
#endif
