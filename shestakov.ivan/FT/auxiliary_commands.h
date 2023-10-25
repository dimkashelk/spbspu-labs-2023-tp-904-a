#ifndef UNTITLED4_AUXILIARY_COMMANDS_H
#define UNTITLED4_AUXILIARY_COMMANDS_H
#include <iostream>
#include <map>
#include "dictionary.h"

namespace shestakov
{
  void printInvalidCommand(std::ostream& out);
  void printInvalidArgument(std::ostream &out);
  void skipUntilNewLine(std::istream& in);
  bool searchDict(const my_map &dictionaries, const std::string &dict_name);
}
#endif
